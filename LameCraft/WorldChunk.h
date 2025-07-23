#ifndef WORLDCHUNK_H
#define WORLDCHUNK_H

#include <psptypes.h>
#include <string>
#include "Blocks.h"
#include "SimpleMeshChunk2.h"

class WorldChunk
{
public:
    static const int CHUNK_SIZE = 32;
    static const int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    
    WorldChunk();
    WorldChunk(int chunkX, int chunkY, int chunkZ);
    ~WorldChunk();
    
    // Coordinate management
    int getChunkX() const { return m_chunkX; }
    int getChunkY() const { return m_chunkY; }
    int getChunkZ() const { return m_chunkZ; }
    
    void setChunkCoords(int x, int y, int z);
    
    // Block access
    block_t getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, block_t blockType);
    
    block_t getBlockSettings(int x, int y, int z) const;
    void setBlockSettings(int x, int y, int z, block_t settings);
    
    // World position conversion
    int getWorldX(int localX) const { return m_chunkX * CHUNK_SIZE + localX; }
    int getWorldY(int localY) const { return m_chunkY * CHUNK_SIZE + localY; }
    int getWorldZ(int localZ) const { return m_chunkZ * CHUNK_SIZE + localZ; }
    
    // State management
    bool isLoaded() const { return m_isLoaded; }
    void setLoaded(bool loaded) { m_isLoaded = loaded; }
    
    bool isDirty() const { return m_isDirty; }
    void setDirty(bool dirty) { m_isDirty = dirty; }
    
    bool isEmpty() const { return m_isEmpty; }
    void setEmpty(bool empty) { m_isEmpty = empty; }
    
    // Rendering mesh
    SimpleMeshChunk* getRenderMesh() { return m_renderMesh; }
    void setRenderMesh(SimpleMeshChunk* mesh) { m_renderMesh = mesh; }
    
    // File operations
    bool saveToFile(const std::string& worldPath) const;
    bool loadFromFile(const std::string& worldPath);
    
    // Clear all blocks
    void clear();
    
    // Check if local coordinates are valid
    static bool isValidLocalCoord(int x, int y, int z);
    
private:
    int m_chunkX;
    int m_chunkY; 
    int m_chunkZ;
    
    block_t* m_blocks;
    block_t* m_blockSettings;
    
    bool m_isLoaded;
    bool m_isDirty;
    bool m_isEmpty;
    
    SimpleMeshChunk* m_renderMesh;
    
    // Helper function for array indexing
    int getBlockIndex(int x, int y, int z) const;
    
    // File path generation
    std::string getChunkFilePath(const std::string& worldPath) const;
};

// Chunk coordinate structure for use in maps
struct ChunkCoord
{
    int x, y, z;
    
    ChunkCoord() : x(0), y(0), z(0) {}
    ChunkCoord(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    
    bool operator<(const ChunkCoord& other) const
    {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
    
    bool operator==(const ChunkCoord& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

#endif