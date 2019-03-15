#pragma once

#include <cstdio>
#include <cstring>
#include <vector>

//error handling
void printError(char *errorMessage);

//helper functions

bool isPowerOfTwo(long long x);
int log(long long x);
long long hexadecimalToDecimal(char hexVal[]);

//I/O

std::vector<long long> readTrace(char filePath[]); // takes in file path as parameter (use this)
std::vector<long long> readTrace(FILE *trace); // takes in file pointer as parameter 

//cache classes

class CacheLine {
    
    private:
        bool valid; // true when block is present in cache, false when no block is present
        long long tag;
        int blockSize;

    public:
        CacheLine(int blockSize);
        
        bool isValid();
        long long getTag();
        void setValid(bool valid);
        void setTag(long long tag); 
};

class Cache {
    
    private:
        int numberOfRows; //Number of rows in cache
        int setAssociativity; //1 for direct mapped
        int numberOfSets;
        int indexSize, offsetSize;
        long long hits, misses;
        std::vector<CacheLine> cacheLines;
        std::vector<int> nextFreeBlockInSet;
        //set is full if nextFreeBlockInSet == setAssociativity

    public:
        Cache(int numberOfRows, int blockSize, int setAssociativity = 1);

        void incHits(); //Must be called when there is a cache hit
        void incMisses(); //Must be called when there is a cache miss
        
        bool isDataInCache(long long address);
        bool isDataInCache(long long index, long long tag);
        bool isSetFull(long long index);
        void insertDataToCache(long long address); //will insert data only if free cacheLines are available and return true (else return false)
        void insertDataToCache(long long index, long long tag);
        void evictAndInsertBlock(long long evictionAddress, long long insertionAddress); //A block is evicted when some other block is inserted
        void evictAndInsertBlock(long long eIndex, long long eTag, long long iIndex, long long iTag);
        
        double hitRate();
        double missRate();
        long long getNumberOfHits(); //for debugging
        long long getNumberOfMisses(); //for debugging
        long long getTagFromAddress(long long address);
        long long getIndexFromAddress(long long address);

        void displayCache(); //for debugging
};
