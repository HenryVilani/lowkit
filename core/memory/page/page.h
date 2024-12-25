#ifndef _LOWKIT_PAGEKIT_H_
#define _LOWKIT_PAGEKIT_H_

#include <Windows.h>
#include "../../../data/memory.h"
#include "../../../data/process.h"

namespace LowKit {

	namespace Memory {

		namespace Page {

			bool getPage(ProcessInfo process, void* address, PageInfo* page);
			bool getAllPages(ProcessInfo process, std::vector<PageInfo>* pages);
			bool allocPage(ProcessInfo process, void* address, int size, DWORD protection, PageInfo* page);
			bool changeProtection(ProcessInfo process, void* address, size_t size, DWORD protection);
			bool changeProtection(ProcessInfo process, PageInfo* page, DWORD protection);

		}

	}
}


bool LowKit::Memory::Page::getPage(ProcessInfo process, void* address, PageInfo* page) {

    SYSTEM_INFO system_info;
    MEMORY_BASIC_INFORMATION mem_info;

    GetSystemInfo(&system_info);

    if (VirtualQueryEx(process.internal.handle, address, &mem_info, sizeof(mem_info)) != ERROR_INVALID_PARAMETER) {

        page->regionSize = mem_info.RegionSize;
        page->pageStart = mem_info.BaseAddress;
        page->pageEnd = (void*)((char*)mem_info.BaseAddress + mem_info.RegionSize);
        page->pageProtection = mem_info.Protect;
        page->allocationStart = mem_info.AllocationBase;
        page->allocationProtetion = mem_info.AllocationProtect;
        page->state = mem_info.State;
        page->internal = mem_info;

        return true;

    }

    return false;
}

bool LowKit::Memory::Page::getAllPages(ProcessInfo process, std::vector<PageInfo>* pages) {

    PageInfo page;

    bool status = LowKit::Memory::Page::getPage(process, (void*)process.address, &page);

    while (status) {

        pages->push_back(page);

        status = LowKit::Memory::Page::getPage(process, (void*)process.address, &page);

    }

    return true;

}

bool LowKit::Memory::Page::allocPage(ProcessInfo process, void* address, int size, DWORD protection, PageInfo* page) {

    void* page_address = VirtualAllocEx(process.internal.handle, address, size, protection, PAGE_EXECUTE_READWRITE);
    return LowKit::Memory::Page::getPage(process, page_address, page);

}

bool LowKit::Memory::Page::changeProtection(ProcessInfo process, void* address, size_t size, DWORD protection) {

    DWORD old_protection;

    return VirtualProtectEx(process.internal.handle, address, size, protection, &old_protection);

}

bool LowKit::Memory::Page::changeProtection(ProcessInfo process, PageInfo* page, DWORD protection) {

    DWORD old_protection;

    return VirtualProtectEx(process.internal.handle, page->pageStart, page->regionSize, protection, &old_protection);

}


#endif
