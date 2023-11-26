#pragma once

#ifndef BASEIPC_H
#define BASEIPC_H

#include "BaseLibrary.h"

#define AFC_PIPE_ACCESS_READ	(0x1)
#define AFC_PIPE_ACCESS_WRITE	(0x2)
#define AFC_PIPE_ACCESS_ALL		(0x3)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef void* AFC_PIPE; // nullptr is fail.

	/**
	* @brief check whether the pipe is available(opened).
	* @param PipeName name
	* @param Millisec timeout(millisecond)
	* @author acgnfun
	* @date 2023/11/22
	* @return int(bool)
	*/
	AF_EXPORT int AFC_IsPipeExistsA(const char* PipeName, int MilliSec = 1ul);

	/**
	* @brief check whether the pipe is available(opened).
	* @param PipeName name
	* @param Millisec timeout(millisecond)
	* @author acgnfun
	* @date 2023/11/22
	* @return int(bool)
	*/
	AF_EXPORT int AFC_IsPipeExistsW(const wchar_t* PipeName, int MilliSec = 1ul);

	/**
	* @brief create a pipe(server) (if it doesn't exist).
	* @param PipeName name
	* @param PipeMode access mode, such as 'AFC_PIPE_ACCCESS_XX'
	* @author acgnfun
	* @date 2023/11/22
	* @return AFC_PIPE handle
	*/
	AF_EXPORT AFC_PIPE AFC_CreatePipeA(const char* PipeName, int PipeMode); // need destory

	/**
	* @brief create a pipe(server) (if it doesn't exist).
	* @param PipeName name
	* @param PipeMode access mode, such as 'AFC_PIPE_ACCCESS_XX'
	* @author acgnfun
	* @date 2023/11/22
	* @return AFC_PIPE handle
	*/
	AF_EXPORT AFC_PIPE AFC_CreatePipeW(const wchar_t* PipeName, int PipeMode); // need destory

	/**
	* @brief open a created pipe(server)(not opened).
	* @author acgnfun
	* @date 2023/11/22
	* @return int(bool)
	*/
	AF_EXPORT int AFC_OpenPipe(AFC_PIPE PipeHandle);

	/**
	* @brief close an opened pipe(server).
	* @author acgnfun
	* @date 2023/11/22
	* @return none
	*/
	AF_EXPORT void AFC_ClosePipe(AFC_PIPE PipeHandle);

	/**
	* @brief connect to an opened pipe.
	* @param PipeName name
	* @param PipeMode access mode, such as 'AFC_PIPE_ACCCESS_XX'
	* @author acgnfun
	* @date 2023/11/22
	* @return AFC_PIPE handle
	*/
	AF_EXPORT AFC_PIPE AFC_ConnectPipeA(const char* PipeName, int PipeMode); // need destory

	/**
	* @brief connect to an opened pipe.
	* @param PipeName name
	* @param PipeMode access mode, such as 'AFC_PIPE_ACCCESS_XX'
	* @author acgnfun
	* @date 2023/11/22
	* @return AFC_PIPE handle
	*/
	AF_EXPORT AFC_PIPE AFC_ConnectPipeW(const wchar_t* PipeName, int PipeMode); // need destory

	/**
	* @brief destroy pipe handle which is created by 'AFC_CreatePipeX' or 'AFC_ConnectPipeX'.
	* @param PipeHandle handle
	* @author acgnfun
	* @date 2023/11/22
	* @return none
	*/
	AF_EXPORT void AFC_DestroyPipe(AFC_PIPE PipeHandle);

	// TCP

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // !BASEIPC_H
