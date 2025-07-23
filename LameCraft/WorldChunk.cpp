#include "WorldChunk.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>

WorldChunk::WorldChunk()
    : m_chunkX(0), m_chunkY(0), m_chunkZ(0), m_blocks(NULL), m_blockSettings(NULL),
      m_isLoaded(false), m_isDirty(false), m_isEmpty(true), m_renderMesh(NULL)
{
    m_blocks = new block_t[CHUNK_VOLUME];
    m_blockSettings = new block_t[CHUNK_VOLUME];
    clear();
}

WorldChunk::WorldChunk(int chunkX, int chunkY, int chunkZ)
    : m_chunkX(chunkX), m_chunkY(chunkY), m_chunkZ(chunkZ), m_blocks(NULL), m_blockSettings(NULL),
      m_isLoaded(false), m_isDirty(false), m_isEmpty(true), m_renderMesh(NULL)
{
    m_blocks = new block_t[CHUNK_VOLUME];
    m_blockSettings = new block_t[CHUNK_VOLUME];
    clear();
}

WorldChunk::~WorldChunk()
{
    if (m_blocks)
    {
        delete[] m_blocks;
        m_blocks = NULL;
    }
    
    if (m_blockSettings)
    {
        delete[] m_blockSettings;
        m_blockSettings = NULL;
    }
    
    if (m_renderMesh)
    {
        delete m_renderMesh;
        m_renderMesh = NULL;
    }
}

void WorldChunk::setChunkCoords(int x, int y, int z)
{
    m_chunkX = x;
    m_chunkY = y;
    m_chunkZ = z;
}

block_t WorldChunk::getBlock(int x, int y, int z) const
{
    if (!isValidLocalCoord(x, y, z) || !m_blocks)
        return 0;
    
    return m_blocks[getBlockIndex(x, y, z)];
}

void WorldChunk::setBlock(int x, int y, int z, block_t blockType)
{
    if (!isValidLocalCoord(x, y, z) || !m_blocks)
        return;
    
    int index = getBlockIndex(x, y, z);
    if (m_blocks[index] != blockType)
    {
        m_blocks[index] = blockType;
        m_isDirty = true;
        
        // Update empty status
        if (blockType != 0)
            m_isEmpty = false;
    }
}

block_t WorldChunk::getBlockSettings(int x, int y, int z) const
{
    if (!isValidLocalCoord(x, y, z) || !m_blockSettings)
        return 0;
    
    return m_blockSettings[getBlockIndex(x, y, z)];
}

void WorldChunk::setBlockSettings(int x, int y, int z, block_t settings)
{
    if (!isValidLocalCoord(x, y, z) || !m_blockSettings)
        return;
    
    int index = getBlockIndex(x, y, z);
    if (m_blockSettings[index] != settings)
    {
        m_blockSettings[index] = settings;
        m_isDirty = true;
    }
}

void WorldChunk::clear()
{
    if (m_blocks)
        memset(m_blocks, 0, sizeof(block_t) * CHUNK_VOLUME);
    
    if (m_blockSettings)
        memset(m_blockSettings, 0, sizeof(block_t) * CHUNK_VOLUME);
    
    m_isEmpty = true;
    m_isDirty = true;
}

bool WorldChunk::isValidLocalCoord(int x, int y, int z)
{
    return x >= 0 && x < CHUNK_SIZE && 
           y >= 0 && y < CHUNK_SIZE && 
           z >= 0 && z < CHUNK_SIZE;
}

int WorldChunk::getBlockIndex(int x, int y, int z) const
{
    return x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
}

std::string WorldChunk::getChunkFilePath(const std::string& worldPath) const
{
    std::stringstream ss;
    ss << worldPath << "/chunks/chunk_" << m_chunkX << "_" << m_chunkY << "_" << m_chunkZ << ".dat";
    return ss.str();
}

bool WorldChunk::saveToFile(const std::string& worldPath) const
{
    if (!m_isDirty || !m_blocks || !m_blockSettings)
        return true;
    
    std::string filePath = getChunkFilePath(worldPath);
    std::ofstream file(filePath.c_str(), std::ios::binary);
    
    if (!file.is_open())
        return false;
    
    // Write chunk header
    file.write(reinterpret_cast<const char*>(&m_chunkX), sizeof(int));
    file.write(reinterpret_cast<const char*>(&m_chunkY), sizeof(int));
    file.write(reinterpret_cast<const char*>(&m_chunkZ), sizeof(int));
    file.write(reinterpret_cast<const char*>(&m_isEmpty), sizeof(bool));
    
    // Write block data
    file.write(reinterpret_cast<const char*>(m_blocks), sizeof(block_t) * CHUNK_VOLUME);
    file.write(reinterpret_cast<const char*>(m_blockSettings), sizeof(block_t) * CHUNK_VOLUME);
    
    file.close();
    return true;
}

bool WorldChunk::loadFromFile(const std::string& worldPath)
{
    std::string filePath = getChunkFilePath(worldPath);
    std::ifstream file(filePath.c_str(), std::ios::binary);
    
    if (!file.is_open())
        return false;
    
    if (!m_blocks || !m_blockSettings)
        return false;
    
    // Read chunk header
    int fileChunkX, fileChunkY, fileChunkZ;
    file.read(reinterpret_cast<char*>(&fileChunkX), sizeof(int));
    file.read(reinterpret_cast<char*>(&fileChunkY), sizeof(int));
    file.read(reinterpret_cast<char*>(&fileChunkZ), sizeof(int));
    file.read(reinterpret_cast<char*>(&m_isEmpty), sizeof(bool));
    
    // Verify chunk coordinates match
    if (fileChunkX != m_chunkX || fileChunkY != m_chunkY || fileChunkZ != m_chunkZ)
    {
        file.close();
        return false;
    }
    
    // Read block data
    file.read(reinterpret_cast<char*>(m_blocks), sizeof(block_t) * CHUNK_VOLUME);
    file.read(reinterpret_cast<char*>(m_blockSettings), sizeof(block_t) * CHUNK_VOLUME);
    
    file.close();
    
    m_isLoaded = true;
    m_isDirty = false;
    
    return true;
}