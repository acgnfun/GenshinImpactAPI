#pragma once

#ifndef BASEDOWNLOAD_H
#define BASEDOWNLOAD_H

#include "BaseLibrary.h"

#define AFC_DOWNLOAD_CONTINUE		(1)
#define AFC_DOWNLOAD_STOP			(0)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef int(*AFC_DownloadCB)(uintmax_t total_bytes, uintmax_t download_bytes, uintmax_t speed_bytes);

	AF_EXPORT int AFC_DownloadA(const char* Url, const char* Path, AFC_DownloadCB Callback = nullptr);

	AF_EXPORT int AFC_DownloadW(const wchar_t* Url, const wchar_t* Path, AFC_DownloadCB Callback = nullptr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEDOWNLOAD_H
