#ifndef _LOWKIT_MODULEINFO_H_
#define _LOWKIT_MODULEINFO_H_

#include <Windows.h>
#include <string>

struct ModuleInternalInfo {

    HMODULE handle;    

};

struct ModuleInfo {


    std::string name;
    BYTE* baseAddress;
    int moduleSize;

    ModuleInternalInfo internal;

};

#endif