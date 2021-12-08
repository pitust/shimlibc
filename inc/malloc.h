#pragma once

#include <stdlib.h>

/**
 * @brief Assign blocks of memory for use by malloc().
 *
 * Initializes the malloc() backend with a memory address and memory pool size.
 *	This memory is assumed to be owned by malloc() and is vended out when memory is requested.
 * 	Multiple blocks can be added.
 *
 * NOTE: This API must be called before malloc() can be used. If you call malloc() before
 * 	allocating memory, malloc() will return NULL because there is no available memory
 *	to provide to the user.
 *
 * @param addr Pointer to the memory block address that you are providing to malloc()
 * @param size Size of the memory block that you are providing to malloc()
 */
void malloc_addblock(void* addr, size_t size);
