#ifndef _LOWKIT_PROCESSKIT_H_
#define _LOWKIT_PROCESSKIT_H_

#include "../../data/module.h"
#include "../../data/process.h"
#include "./module/module.h"
#include "./memory.h"

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

namespace LowKit {

    namespace Process {

        std::vector<std::string> listProcess();
        ProcessInfo attach(std::string process, DWORD tool_flag = TH32CS_SNAPALL, DWORD process_flag = PROCESS_ALL_ACCESS);
        bool detach(ProcessInfo* process);


    }

}

std::vector<std::string> LowKit::Process::listProcess() {

    std::vector<std::string> process_list;

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 sentry;
    sentry.dwSize = sizeof(PROCESSENTRY32);

    bool status = Process32First(snap, &sentry);

    while (status) {

        process_list.push_back(std::string(sentry.szExeFile));
        status = Process32Next(snap, &sentry);

    }

    return process_list;

}


bool LowKit::Process::detach(ProcessInfo* process) {

    if (process->attached) {

        return CloseHandle(process->internal.handle);

    }else {

        return false;

    }

    


}


ProcessInfo LowKit::Process::attach(std::string process, DWORD tool_flag, DWORD process_flag) {

    ProcessInfo info;
    info.attached = false;
    info.process_flag = process_flag;
    info.tool_flag = tool_flag;

    HANDLE snap = CreateToolhelp32Snapshot(tool_flag, 0);

    PROCESSENTRY32 sentry;
    sentry.dwSize = sizeof(PROCESSENTRY32);

    bool status = Process32First(snap, &sentry);

    while (status) {

        if (status && std::string(sentry.szExeFile) == process) {

            HANDLE handle = OpenProcess(process_flag, false, sentry.th32ProcessID);


            info.name = std::string(sentry.szExeFile);
            info.pid = sentry.th32ProcessID;
            info.internal.handle = handle;
            info.internal.pcPriClassBase = sentry.pcPriClassBase;
            info.internal.cntThreads = sentry.cntThreads;
            info.internal.parentPid = sentry.th32ParentProcessID;
            info.internal.size = sentry.dwSize;
            info.attached = true;

            ModuleInfo mod = LowKit::Process::Module::getModule(info, "Notepad.exe");
            info.address = mod.baseAddress;

            return info;

        }

        status = Process32Next(snap, &sentry);

    }

    return info;

}

bool LowKit::Process::Module::loadModule(ProcessInfo process, std::string module_path) {

    PageInfo page;

    LowKit::Memory::Page::allocPage(process, NULL, MAX_PATH, PAGE_READWRITE, &page);
    const char* c_path = module_path.c_str();
    LowKit::Memory::write<const char*>(process, page.pageStart, c_path, module_path.size() + 1);

    //CreateThread

    return false;

}

#endif