#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <cstdlib> // malloc(), free()

namespace MyOwnMemoryManagement
{
extern unsigned deletions;
}

void* operator new[](size_t size);

void operator delete[](void* memory2remove) noexcept;
void operator delete[](void* memory2remove, size_t) noexcept;

#endif // MEMORY_MANAGEMENT_H
