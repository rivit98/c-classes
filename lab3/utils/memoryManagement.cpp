#include "memoryManagement.h"


unsigned MyOwnMemoryManagement::deletions = 0;

void *operator new[](size_t size)
{
    void* newMemory = malloc(size);
    return newMemory;
}

void operator delete[](void *memory2remove) noexcept
{
    ++MyOwnMemoryManagement::deletions;
    free(memory2remove);
}

void operator delete[](void* memory2remove, size_t) noexcept
{
    ++MyOwnMemoryManagement::deletions;
    free(memory2remove);
}
