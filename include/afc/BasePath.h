#pragma once

#ifndef BASEPATH_H
#define BASEPATH_H

#include "BaseLibrary.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/**
	* @brief get the path to the current exe file.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnFun
	* @date 2023/11/22
	* @return minimum buffer size(elem number) (if it is greater than bufsize, it means failure)
	*/
	AF_EXPORT int AFC_ProgramFilePathA(char* Buffer, int BufSize);

	/**
	* @brief get the path to the current exe file.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnFun
	* @date 2023/11/22
	* @return minimum buffer size(elem number) (if it is greater than bufsize, it means failure)
	*/
	AF_EXPORT int AFC_ProgramFilePathW(wchar_t* Buffer, int BufSize);

	/**
	* @briefget the path to the directory where the current exe file is located.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnFun
	* @date 2023/11/22
	* @return minimum buffer size(elem number) (if it is greater than bufsize, it means failure)
	*/
	AF_EXPORT int AFC_ProgramFolderPathA(char* Buffer, int BufSize);

	/**
	* @brief get the path to the directory where the current exe file is located.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnFun
	* @date 2023/11/22
	* @return minimum buffer size(elem number) (if it is greater than bufsize, it means failure)
	*/
	AF_EXPORT int AFC_ProgramFolderPathW(wchar_t* Buffer, int BufSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEPATH_H
