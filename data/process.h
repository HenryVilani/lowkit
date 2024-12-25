#ifndef _LOWKIT_PROCESS_TYPE_H_
#define _LOWKIT_PROCESS_TYPE_H_

#include <Windows.h>
#include <string>

struct ProcessInternalInfo {

    HANDLE handle;
    DWORD size;
    DWORD parentPid;
    DWORD cntThreads;
    LONG pcPriClassBase;

};

struct ProcessInfo {

    std::string name;
    DWORD pid;
    void* address;

    bool attached;
    DWORD process_flag;
    DWORD tool_flag;

    ProcessInternalInfo internal;

};

struct ThreadInternalInfo {

    HANDLE handle;

};

struct ThreadInfo {

    ThreadInternalInfo internal;

};

#endif