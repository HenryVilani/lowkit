#ifndef _LOWKIT_MODULEKIT_H_
#define _LOWKIT_MODULEKIT_H_

#include "../../../data/process.h"
#include "../../../data/module.h"

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

namespace LowKit{

	namespace Process {

        namespace Module {

            ModuleInfo getModule(ProcessInfo process, std::string name);
            std::vector<ModuleInfo> getModules(ProcessInfo process);
            bool loadModule(ProcessInfo process, std::string module_path);

        }

	}

}

ModuleInfo LowKit::Process::Module::getModule(ProcessInfo process, std::string name) {

    ModuleInfo moduleInfo;

    if (process.attached) {

        HANDLE snap = CreateToolhelp32Snapshot(process.tool_flag, process.pid);

        MODULEENTRY32 sentry;
        sentry.dwSize = sizeof(MODULEENTRY32);

        bool status = Module32First(snap, &sentry);

        while (status) {

            if (status && std::string(sentry.szModule) == name) {

                moduleInfo.name = std::string(sentry.szExePath);
                moduleInfo.internal.handle = sentry.hModule;
                moduleInfo.baseAddress = sentry.modBaseAddr;
                moduleInfo.moduleSize = sentry.modBaseSize;

                return moduleInfo;

            }

        }

    }

    return moduleInfo;

}

std::vector<ModuleInfo> LowKit::Process::Module::getModules(ProcessInfo process) {

    std::vector<ModuleInfo> modules;

    HANDLE snap = CreateToolhelp32Snapshot(process.tool_flag, process.pid);

    MODULEENTRY32 sentry;
    sentry.dwSize = sizeof(MODULEENTRY32);

    bool status = Module32First(snap, &sentry);

    while (status) {

        ModuleInfo moduleInfo;
        moduleInfo.baseAddress = sentry.modBaseAddr;
        moduleInfo.name = std::string(sentry.szModule);
        moduleInfo.internal.handle = sentry.hModule;
        moduleInfo.moduleSize = sentry.modBaseSize;
        modules.push_back(moduleInfo);

        status = Module32Next(snap, &sentry);

    }

    return modules;

}


#endif