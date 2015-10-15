/**
* Author :CZ cz.theng@gmail.com
* 
* Copyright (c) 2015 CZ cz.theng@gmail.com

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifdef __ANDROID__
#include <unwind.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <jni.h>
#endif

#include "atrace.h"

#ifdef __ANDROID__

typedef struct backtrace_info_t
{
    void** current;
    void** end;
} backtrace_info;

static _Unwind_Reason_Code unwind_callback(struct _Unwind_Context* context, void* arg)
{
	backtrace_info *info = (backtrace_info *) arg;
	_Unwind_Word pc = _Unwind_GetIP(context);
    if (pc) {
        if (info->current == info->end) {
            return _URC_END_OF_STACK;
        } else {
            *info->current++ = (void *)pc;
        }
    }
    return _URC_NO_REASON;
}

static size_t capture_backtrace(void** buffer, size_t max)
{
	backtrace_info info = {buffer, buffer + max};
    _Unwind_Backtrace(unwind_callback, &info);

    return info.current - buffer;
}

static void dump_backtrace(char *destBuf, size_t *destLen, void** buffer, size_t count)
{
	if (NULL==destBuf || NULL==destLen || destLen <=0 || NULL==buffer || count <=0 ) {
		return ;
	}
	size_t idx;
	size_t desSize = *destLen;
	int tail = 0;

    for (idx = 1; idx < count; ++idx) {
        const void *addr = buffer[idx];
        const char *symbol = "";

        Dl_info info;
        if (dladdr(addr, &info) && info.dli_sname) {
            symbol = info.dli_sname;
        }

        //os << "  #" << std::setw(2) << idx << ": " << addr << "  " << symbol << "\n";
        if (desSize - tail <=0) {
        	return ;
        }
        int rst = snprintf(destBuf+tail, desSize-tail, "    #%02d:0x%x    %s \n", idx-1, (_Unwind_Word *)addr, symbol);
        if (rst <0 ) {
        	return ;
        } else {
        	tail += rst;
        }
    }
}

#endif

void atrace()
{
#ifdef __ANDROID__
    size_t max = 30;
    void* buffer[max];

    size_t destLen = 1024;
    char destBuf[destLen];
    memset(destBuf, 0, destLen);

    dump_backtrace(destBuf, &destLen, buffer, capture_backtrace(buffer, max));

    __android_log_print(ANDROID_LOG_INFO, "ATRACE", "%s", destBuf);
#endif
}

int traceinfo(char *buf, int *len) 
{
	if (NULL == buf || NULL == len || *len < 0) {
		return -1;
	}
#ifdef __ANDROID__
    size_t max = 30;
    void* buffer[max];
    memset(buf, 0, *len);
    dump_backtrace(buf, len, buffer, capture_backtrace(buffer, max));
    return 0;
#endif
	return -1;
}
