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
	* @author acgnfun
	* @date 2023/12/2
	* @return minimum buffer size(elem number)
	* @return if it is greater than bufsize, it means failure.
	* @return If the value is -1, a fatal error has occurred and the function will never respond correctly.
	*/
	AF_EXPORT int AFC_ProgramFilePathA(char* Buffer, int BufSize);

	/**
	* @brief get the path to the current exe file.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnfun
	* @date 2023/12/2
	* @return minimum buffer size(elem number)
	* @return if it is greater than bufsize, it means failure.
	* @return If the value is -1, a fatal error has occurred and the function will never respond correctly.
	*/
	AF_EXPORT int AFC_ProgramFilePathW(wchar_t* Buffer, int BufSize);

	/**
	* @briefget the path to the directory where the current exe file is located.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnfun
	* @date 2023/12/2
	* @return minimum buffer size(elem number)
	* @return if it is greater than bufsize, it means failure.
	* @return If the value is -1, a fatal error has occurred and the function will never respond correctly.
	*/
	AF_EXPORT int AFC_ProgramFolderPathA(char* Buffer, int BufSize);

	/**
	* @brief get the path to the directory where the current exe file is located.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnfun
	* @date 2023/12/2
	* @return minimum buffer size(elem number)
	* @return if it is greater than bufsize, it means failure.
	* @return If the value is -1, a fatal error has occurred and the function will never respond correctly.
	*/
	AF_EXPORT int AFC_ProgramFolderPathW(wchar_t* Buffer, int BufSize);

	/**
	* @brief Get the temporary file path.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnfun
	* @date 2023/12/2
	* @return minimum buffer size(elem number)
	* @return if it is greater than bufsize, it means failure.
	* @return If the value is -1, a fatal error has occurred and the function will never respond correctly.
	*/
	AF_EXPORT int AFC_TempPathA(char* Buffer, int BufSize);

	/**
	* @brief Get the temporary file path.
	* @param Buffer memory area.
	* @param BufSize memory size(elem number).
	* @author acgnfun
	* @date 2023/12/2
	* @return minimum buffer size(elem number)
	* @return if it is greater than bufsize, it means failure.
	* @return If the value is -1, a fatal error has occurred and the function will never respond correctly.
	*/
	AF_EXPORT int AFC_TempPathW(wchar_t* Buffer, int BufSize);

	/**
	* @brief Rename the path from old name to new.
	* @param Old_p Old path name.
	* @param New_p New path name.
	* @author acgnfun
	* @date 2023/12/18
	* @return int(bool)
	*/
	AF_EXPORT int AFC_RenamePathA(const char* Old_p, const char* New_p);

	/**
	* @brief Rename the path from old name to new.
	* @param Old_p Old path name.
	* @param New_p New path name.
	* @author acgnfun
	* @date 2023/12/18
	* @return int(bool)
	*/
	AF_EXPORT int AFC_RenamePathW(const wchar_t* Old_p, const wchar_t* New_p);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEPATH_H
