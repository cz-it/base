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

#ifdef CZ_BASE_ANDROID_ATRACE
#define CZ_BASE_ANDROID_ATRACE

#ifdef __cplusplus 
extern "C" {
#endif

/**
* Print Invoke trace info .
*/
extern void atrace();

/**
* Get Trace Info.
*
* @param: buf , buf to store info message
* @param: len, a value-result param indicate length of buf
* @return: 0 on success and effectiv lenght in len
*/

extern int traceinfo(char *buf, int *len);

#ifdef __cplusplus
}
#endif
#endif