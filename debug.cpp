#include "debug.h"
#include <windows.h>

//void DbgOutput(const char* file, const int line, const WCHAR* pFormat, ...)
//{
//    WCHAR   buffer[1024] = { 0 };
//    int string_length = wsprintf(buffer, L"%hs(%d): ", file, line);
//
//    va_list AdditionalParameters;
//    va_start(AdditionalParameters, pFormat);
//    wvsprintf(buffer + string_length, pFormat, AdditionalParameters);
//    va_end(AdditionalParameters);
//
//    OutputDebugString(buffer);
//}

void DEBUG_OUT(std::wstring line)
{
	OutputDebugString(line.c_str());
}