#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <psptypes.h>
#include <Aurora/Math/Vector3.h>
#include "WorldChunk.h"
#include "Blocks.h"

using namespace Aurora::Math;

class WorldGenerator;
class CraftWorld;

class ChunkManager
{
public:
    ChunkManager();
    ~ChunkManager();
    
    // Initialization
    void initialize(const std::string& worldPath, int renderDistance = 8);
    void setWorldGenerator(WorldGenerator* generator) { m_worldGenerator = generator; }
    void setCraftWorld(CraftWorld* world) { m_craftWorld = world; }
    
    // Player position management
    void updatePlayerPosition(const Vector3& worldPos);
    void updateLoadedChunks();
    
    // Block access (world coordinates)
    block_t getBlock(int worldX, int worldY, int worldZ);
    void setBlock(int worldX, int worldY, int worldZ, block_t blockType);
    
    block_t getBlockSettings(int worldX, int worldY, int worldZ);
    void setBlockSettings(int worldX, int worldY, int worldZ, block_t settings);
    
    // Chunk access
    WorldChunk* getChunk(int chunkX, int chunkY, int chunkZ);
    WorldChunk* getChunkAtWorldPos(int worldX, int worldY, int worldZ);
    
    // Chunk loading/unloading
    bool loadChunk(int chunkX, int chunkY, int chunkZ);
    void unloadChunk(int chunkX, int chunkY, int chunkZ);
    void unloadDistantChunks();
    
    // Save/Load operations
    void saveAllChunks();
    void saveChunk(WorldChunk* chunk);
    
    // Utility functions
    static ChunkCoord worldToChunkCoord(int worldX, int worldY, int worldZ);
    static void worldToLocalCoord(int worldX, int worldY, int worldZ, 
                                  int& chunkX, int& chunkY, int& chunkZ,
                                  int& localX, int& localY, int& localZ);
    
    // Getters
    int getRenderDistance() const { return m_renderDistance; }
    void setRenderDistance(int distance);
    
    const std::vector<WorldChunk*>& getLoadedChunks() const { return m_loadedChunksList; }
    
    // Chunk management
    void clearAllChunks();
    int getLoadedChunkCount() const { return static_cast<int>(m_loadedChunks.size()); }
    
    // For rendering system
    std::vector<int> getNearestChunkIds();
    
private:
    std::map<ChunkCoord, WorldChunk*> m_loadedChunks;
    std::vector<WorldChunk*> m_loadedChunksList; // For iteration
    
    std::string m_worldPath;
    int m_renderDistance;
    
    Vector3 m_lastPlayerChunkPos;
    
    WorldGenerator* m_worldGenerator;
    CraftWorld* m_craftWorld;
    
    // Helper functions
    bool isChunkInRange(const ChunkCoord& chunkCoord, const ChunkCoord& playerChunk) const;
    float getChunkDistance(const ChunkCoord& chunk1, const ChunkCoord& chunk2) const;
    
    // Chunk generation
    void generateChunk(WorldChunk* chunk);
    
    // File system helpers
    bool createChunkDirectory() const;
    
    // Memory management
    void cleanupUnusedChunks();
    
    // Constants
    static const int MAX_LOADED_CHUNKS = 250; // Maximum chunks in memory (reduced for PSP)
    static const int UNLOAD_BATCH_SIZE = 12;  // Chunks to unload per frame (reduced)
};

#endif