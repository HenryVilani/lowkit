#ifndef _LOWKIT_THREADKIT_H_
#define _LOWKIT_THREADKIT_H_

#include "../../../data/process.h"
#include <Windows.h>

namespace LowKit {

	namespace Process {

		namespace Thread {

			bool newThread(ProcessInfo process, void* callback, void* param, ThreadInfo* thread);
			// implement newThread with more params
			bool closeThread(ThreadInfo thread);

		}

	}

}

bool LowKit::Process::Thread::newThread(ProcessInfo process, void* callback, void* param, ThreadInfo* thread) {

	HANDLE handle = CreateRemoteThread(process.internal.handle, NULL, NULL, (LPTHREAD_START_ROUTINE)callback, param, NULL, NULL);

	thread->internal.handle = handle;

	return false;

}

bool LowKit::Process::Thread::closeThread(ThreadInfo thread) {

	return CloseHandle(thread.internal.handle);

}



#endif