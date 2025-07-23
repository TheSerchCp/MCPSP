#include "ChunkManager.h"
#include "WorldGenerator.h"
#include "CraftWorld2.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <pspiofilemgr.h>

ChunkManager::ChunkManager()
    : m_renderDistance(6), m_worldGenerator(NULL), m_craftWorld(NULL)
{
    m_lastPlayerChunkPos = Vector3(0, 0, 0);
}

ChunkManager::~ChunkManager()
{
    clearAllChunks();
}

void ChunkManager::initialize(const std::string& worldPath, int renderDistance)
{
    m_worldPath = worldPath;
    m_renderDistance = renderDistance;
    createChunkDirectory();
}

void ChunkManager::updatePlayerPosition(const Vector3& worldPos)
{
    ChunkCoord playerChunk = worldToChunkCoord(static_cast<int>(worldPos.x), 
                                               static_cast<int>(worldPos.y), 
                                               static_cast<int>(worldPos.z));
    
    Vector3 newPlayerChunkPos(static_cast<float>(playerChunk.x), 
                             static_cast<float>(playerChunk.y), 
                             static_cast<float>(playerChunk.z));
    
    // Only update if player moved to a different chunk
    if (newPlayerChunkPos.x != m_lastPlayerChunkPos.x || 
        newPlayerChunkPos.y != m_lastPlayerChunkPos.y || 
        newPlayerChunkPos.z != m_lastPlayerChunkPos.z)
    {
        m_lastPlayerChunkPos = newPlayerChunkPos;
        updateLoadedChunks();
    }
}

void ChunkManager::updateLoadedChunks()
{
    ChunkCoord playerChunk(static_cast<int>(m_lastPlayerChunkPos.x),
                          static_cast<int>(m_lastPlayerChunkPos.y),
                          static_cast<int>(m_lastPlayerChunkPos.z));
    
    // Load chunks around player
    for (int x = playerChunk.x - m_renderDistance; x <= playerChunk.x + m_renderDistance; x++)
    {
        for (int z = playerChunk.z - m_renderDistance; z <= playerChunk.z + m_renderDistance; z++)
        {
            for (int y = playerChunk.y - 2; y <= playerChunk.y + 2; y++) // Limited Y range for performance
            {
                ChunkCoord coord(x, y, z);
                if (isChunkInRange(coord, playerChunk))
                {
                    loadChunk(x, y, z);
                }
            }
        }
    }
    
    // Unload distant chunks
    unloadDistantChunks();
}

block_t ChunkManager::getBlock(int worldX, int worldY, int worldZ)
{
    int chunkX, chunkY, chunkZ;
    int localX, localY, localZ;
    
    worldToLocalCoord(worldX, worldY, worldZ, chunkX, chunkY, chunkZ, localX, localY, localZ);
    
    WorldChunk* chunk = getChunk(chunkX, chunkY, chunkZ);
    if (!chunk)
        return 0;
    
    return chunk->getBlock(localX, localY, localZ);
}

void ChunkManager::setBlock(int worldX, int worldY, int worldZ, block_t blockType)
{
    int chunkX, chunkY, chunkZ;
    int localX, localY, localZ;
    
    worldToLocalCoord(worldX, worldY, worldZ, chunkX, chunkY, chunkZ, localX, localY, localZ);
    
    WorldChunk* chunk = getChunk(chunkX, chunkY, chunkZ);
    if (!chunk)
    {
        // Try to load the chunk
        if (loadChunk(chunkX, chunkY, chunkZ))
            chunk = getChunk(chunkX, chunkY, chunkZ);
    }
    
    if (chunk)
        chunk->setBlock(localX, localY, localZ, blockType);
}

block_t ChunkManager::getBlockSettings(int worldX, int worldY, int worldZ)
{
    int chunkX, chunkY, chunkZ;
    int localX, localY, localZ;
    
    worldToLocalCoord(worldX, worldY, worldZ, chunkX, chunkY, chunkZ, localX, localY, localZ);
    
    WorldChunk* chunk = getChunk(chunkX, chunkY, chunkZ);
    if (!chunk)
        return 0;
    
    return chunk->getBlockSettings(localX, localY, localZ);
}

void ChunkManager::setBlockSettings(int worldX, int worldY, int worldZ, block_t settings)
{
    int chunkX, chunkY, chunkZ;
    int localX, localY, localZ;
    
    worldToLocalCoord(worldX, worldY, worldZ, chunkX, chunkY, chunkZ, localX, localY, localZ);
    
    WorldChunk* chunk = getChunk(chunkX, chunkY, chunkZ);
    if (!chunk)
    {
        if (loadChunk(chunkX, chunkY, chunkZ))
            chunk = getChunk(chunkX, chunkY, chunkZ);
    }
    
    if (chunk)
        chunk->setBlockSettings(localX, localY, localZ, settings);
}

WorldChunk* ChunkManager::getChunk(int chunkX, int chunkY, int chunkZ)
{
    ChunkCoord coord(chunkX, chunkY, chunkZ);
    std::map<ChunkCoord, WorldChunk*>::iterator it = m_loadedChunks.find(coord);
    
    if (it != m_loadedChunks.end())
        return it->second;
    
    return NULL;
}

WorldChunk* ChunkManager::getChunkAtWorldPos(int worldX, int worldY, int worldZ)
{
    ChunkCoord coord = worldToChunkCoord(worldX, worldY, worldZ);
    return getChunk(coord.x, coord.y, coord.z);
}

bool ChunkManager::loadChunk(int chunkX, int chunkY, int chunkZ)
{
    // Check if already loaded
    if (getChunk(chunkX, chunkY, chunkZ))
        return true;
    
    // Check memory limits
    if (static_cast<int>(m_loadedChunks.size()) >= MAX_LOADED_CHUNKS)
    {
        cleanupUnusedChunks();
        if (static_cast<int>(m_loadedChunks.size()) >= MAX_LOADED_CHUNKS)
            return false;
    }
    
    // Create new chunk
    WorldChunk* chunk = new WorldChunk(chunkX, chunkY, chunkZ);
    
    // Try to load from file
    if (!chunk->loadFromFile(m_worldPath))
    {
        // Generate new chunk if file doesn't exist
        generateChunk(chunk);
    }
    
    chunk->setLoaded(true);
    
    // Add to maps
    ChunkCoord coord(chunkX, chunkY, chunkZ);
    m_loadedChunks[coord] = chunk;
    m_loadedChunksList.push_back(chunk);
    
    return true;
}

void ChunkManager::unloadChunk(int chunkX, int chunkY, int chunkZ)
{
    ChunkCoord coord(chunkX, chunkY, chunkZ);
    std::map<ChunkCoord, WorldChunk*>::iterator it = m_loadedChunks.find(coord);
    
    if (it != m_loadedChunks.end())
    {
        WorldChunk* chunk = it->second;
        
        // Save if dirty
        if (chunk->isDirty())
            saveChunk(chunk);
        
        // Remove from list
        std::vector<WorldChunk*>::iterator listIt = std::find(m_loadedChunksList.begin(), 
                                                              m_loadedChunksList.end(), 
                                                              chunk);
        if (listIt != m_loadedChunksList.end())
            m_loadedChunksList.erase(listIt);
        
        // Clean up
        delete chunk;
        m_loadedChunks.erase(it);
    }
}

void ChunkManager::unloadDistantChunks()
{
    ChunkCoord playerChunk(static_cast<int>(m_lastPlayerChunkPos.x),
                          static_cast<int>(m_lastPlayerChunkPos.y),
                          static_cast<int>(m_lastPlayerChunkPos.z));
    
    std::vector<ChunkCoord> chunksToUnload;
    
    for (std::map<ChunkCoord, WorldChunk*>::iterator it = m_loadedChunks.begin(); 
         it != m_loadedChunks.end(); ++it)
    {
        if (!isChunkInRange(it->first, playerChunk))
        {
            chunksToUnload.push_back(it->first);
        }
    }
    
    // Unload chunks in batches to avoid frame drops
    int unloadCount = 0;
    for (std::vector<ChunkCoord>::iterator it = chunksToUnload.begin(); 
         it != chunksToUnload.end() && unloadCount < UNLOAD_BATCH_SIZE; ++it, ++unloadCount)
    {
        unloadChunk(it->x, it->y, it->z);
    }
}

void ChunkManager::saveAllChunks()
{
    for (std::map<ChunkCoord, WorldChunk*>::iterator it = m_loadedChunks.begin(); 
         it != m_loadedChunks.end(); ++it)
    {
        saveChunk(it->second);
    }
}

void ChunkManager::saveChunk(WorldChunk* chunk)
{
    if (chunk && chunk->isDirty())
    {
        chunk->saveToFile(m_worldPath);
        chunk->setDirty(false);
    }
}

ChunkCoord ChunkManager::worldToChunkCoord(int worldX, int worldY, int worldZ)
{
    // Handle negative coordinates properly
    int chunkX = worldX >= 0 ? worldX / WorldChunk::CHUNK_SIZE : (worldX - WorldChunk::CHUNK_SIZE + 1) / WorldChunk::CHUNK_SIZE;
    int chunkY = worldY >= 0 ? worldY / WorldChunk::CHUNK_SIZE : (worldY - WorldChunk::CHUNK_SIZE + 1) / WorldChunk::CHUNK_SIZE;
    int chunkZ = worldZ >= 0 ? worldZ / WorldChunk::CHUNK_SIZE : (worldZ - WorldChunk::CHUNK_SIZE + 1) / WorldChunk::CHUNK_SIZE;
    
    return ChunkCoord(chunkX, chunkY, chunkZ);
}

void ChunkManager::worldToLocalCoord(int worldX, int worldY, int worldZ, 
                                    int& chunkX, int& chunkY, int& chunkZ,
                                    int& localX, int& localY, int& localZ)
{
    ChunkCoord coord = worldToChunkCoord(worldX, worldY, worldZ);
    chunkX = coord.x;
    chunkY = coord.y;
    chunkZ = coord.z;
    
    // Calculate local coordinates within chunk
    localX = worldX - chunkX * WorldChunk::CHUNK_SIZE;
    localY = worldY - chunkY * WorldChunk::CHUNK_SIZE;
    localZ = worldZ - chunkZ * WorldChunk::CHUNK_SIZE;
    
    // Ensure local coordinates are positive
    if (localX < 0) localX += WorldChunk::CHUNK_SIZE;
    if (localY < 0) localY += WorldChunk::CHUNK_SIZE;
    if (localZ < 0) localZ += WorldChunk::CHUNK_SIZE;
}

void ChunkManager::setRenderDistance(int distance)
{
    m_renderDistance = distance;
    updateLoadedChunks();
}

void ChunkManager::clearAllChunks()
{
    saveAllChunks();
    
    for (std::map<ChunkCoord, WorldChunk*>::iterator it = m_loadedChunks.begin(); 
         it != m_loadedChunks.end(); ++it)
    {
        delete it->second;
    }
    
    m_loadedChunks.clear();
    m_loadedChunksList.clear();
}

std::vector<int> ChunkManager::getNearestChunkIds()
{
    std::vector<int> ids;
    for (size_t i = 0; i < m_loadedChunksList.size(); ++i)
    {
        ids.push_back(static_cast<int>(i));
    }
    return ids;
}

bool ChunkManager::isChunkInRange(const ChunkCoord& chunkCoord, const ChunkCoord& playerChunk) const
{
    float distance = getChunkDistance(chunkCoord, playerChunk);
    return distance <= static_cast<float>(m_renderDistance);
}

float ChunkManager::getChunkDistance(const ChunkCoord& chunk1, const ChunkCoord& chunk2) const
{
    float dx = static_cast<float>(chunk1.x - chunk2.x);
    float dz = static_cast<float>(chunk1.z - chunk2.z);
    return sqrt(dx * dx + dz * dz);
}

void ChunkManager::generateChunk(WorldChunk* chunk)
{
    if (!m_worldGenerator || !chunk)
        return;
    
    // Use the WorldGenerator to generate this chunk
    unsigned int seed = 12345; // Default seed, should be configurable
    int worldType = 0; // Default world type
    bool nether = false; // Default overworld
    
    m_worldGenerator->generateChunk(chunk, m_craftWorld, seed, worldType, nether);
}

bool ChunkManager::createChunkDirectory() const
{
    std::string chunkDir = m_worldPath + "/chunks";
    sceIoMkdir(chunkDir.c_str(), 0777);
    return true;
}

void ChunkManager::cleanupUnusedChunks()
{
    ChunkCoord playerChunk(static_cast<int>(m_lastPlayerChunkPos.x),
                          static_cast<int>(m_lastPlayerChunkPos.y),
                          static_cast<int>(m_lastPlayerChunkPos.z));
    
    // Find chunks that are farthest from player
    std::vector<std::pair<float, ChunkCoord> > chunkDistances;
    
    for (std::map<ChunkCoord, WorldChunk*>::iterator it = m_loadedChunks.begin(); 
         it != m_loadedChunks.end(); ++it)
    {
        float distance = getChunkDistance(it->first, playerChunk);
        chunkDistances.push_back(std::make_pair(distance, it->first));
    }
    
    // Sort by distance (farthest first)
    std::sort(chunkDistances.begin(), chunkDistances.end());
    std::reverse(chunkDistances.begin(), chunkDistances.end());
    
    // Unload farthest chunks until we're under the limit (more aggressive cleanup for PSP)
    int chunksToUnload = static_cast<int>(m_loadedChunks.size()) - (MAX_LOADED_CHUNKS * 2 / 3);
    for (int i = 0; i < chunksToUnload && i < static_cast<int>(chunkDistances.size()); ++i)
    {
        const ChunkCoord& coord = chunkDistances[i].second;
        unloadChunk(coord.x, coord.y, coord.z);
    }
}