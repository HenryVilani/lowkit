#ifndef _LOWKIT_MEMORYKIT_H_
#define _LOWKIT_MEMORYKIT_H_

#include <Windows.h>
#include <inttypes.h>
#include <vector>

#include "../../data/process.h"
#include "../../data/memory.h"
#include "./page/page.h"


namespace LowKit {

    namespace Memory {

        template <typename T> bool read(ProcessInfo process, void* address, T* data);
        template <typename T> bool read(ProcessInfo process, void* address, T* data, int length);

        template <typename T> bool write(ProcessInfo process, void* address, T data);
        template <typename T> bool write(ProcessInfo process, void* address, T data, int length);


    }

}

template <typename T> bool LowKit::Memory::read(ProcessInfo process, void* address, T* data) {

    return ReadProcessMemory(process.internal.handle, (void*)address, data, sizeof(T), NULL);

}

template <typename T> bool LowKit::Memory::read(ProcessInfo process, void* address, T* data, int length) {

    return ReadProcessMemory(process.internal.handle, address, data, length, NULL);

}

template <typename T> bool LowKit::Memory::write(ProcessInfo process, void* address, T data) {

    return WriteProcessMemory(process.internal.handle, address, &data, sizeof(T), NULL);

}

template <typename T> bool LowKit::Memory::write(ProcessInfo process, void* address, T data, int length) {

    return WriteProcessMemory(process.internal.handle, address, &data, length, NULL);

}

#endif
