#pragma once

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include "BaseLibrary.h"
#include "objbase.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	AF_EXPORT int AFC_CreateShortCutA(const char* FilePath, const char* ShortCutPath, const char* Description = nullptr, const char* WorkingDir = nullptr, const char* IconPath = nullptr, int IconId = 0);
	AF_EXPORT int AFC_CreateShortCutW(const wchar_t* FilePath, const wchar_t* ShortCutPath, const wchar_t* Description = nullptr, const wchar_t* WorkingDir = nullptr, const wchar_t* IconPath = nullptr, int IconId = 0);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SHORTCUT_H
