#ifndef _LOWKIT_MEMORY_H_
#define _LOWKIT_MEMORY_H_

struct PageInfo {

	void* pageStart;
	void* pageEnd;
	void* allocationStart;
	void* allocationEnd;
	SIZE_T regionSize;
	DWORD allocationProtetion;
	DWORD pageProtection;
	DWORD state;

	MEMORY_BASIC_INFORMATION internal;

};

#endif