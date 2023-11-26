#pragma once

#ifndef BASEDOWNLOAD_H
#define BASEDOWNLOAD_H

#include "BaseLibrary.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/**
	* @brief download file from internet with no progress.
	* @author acgnfun
	* @date 2023/11/21
	* @return none
	*/
	AF_EXPORT void AFC_DownloadA(const char* Url, const char* Path);

	/**
	* @brief download file from internet with no progress (wide).
	* @author acgnfun
	* @date 2023/11/21
	* @return none
	*/
	AF_EXPORT void AFC_DownloadW(const wchar_t* Url, const wchar_t* Path);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEDOWNLOAD_H
