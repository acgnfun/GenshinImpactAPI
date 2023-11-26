#pragma once

#ifndef BASEOPT_H
#define BASEOPT_H

#include "BaseLibrary.h"
#include "OptProc.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	AF_EXPORT AFC_HOPT AFC_CreateOptionProcessor();
	AF_EXPORT void AFC_DestroyOptionProcessor(AFC_HOPT hOpt);
	AF_EXPORT void AFC_BindOption(AFC_HOPT hOpt, int argc, char* argv[]);
	AF_EXPORT int AFC_ProcOption(AFC_HOPT hOpt, AFC_RULE* RuleList);
	AF_EXPORT int AFC_GetOption(AFC_HOPT hOpt, char* buffer, int bufsize); // bool

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEOPT_H
