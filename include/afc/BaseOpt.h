#pragma once

#ifndef BASEOPT_H
#define BASEOPT_H

#include "BaseLibrary.h"

#define AFC_OPT_ARGNUM(x)	int(x)
#define AFC_OPT_NO_ARG		AFC_OPT_ARGNUM(0)
#define AFC_OPT_REQ_ARG		AFC_OPT_ARGNUM(1)
#define AFC_OPT_OPT_ARG		AFC_OPT_ARGNUM(-1)

#define AFC_OPT_ERROR		int(-1) // procopt finish.
#define AFC_OPT_NOT_FOUND	int(-2) // unknown keyword.
#define AFC_OPT_NOT_ENOUGH	int(-3) // argument is not enough to fill rule.

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef void* AFC_HOPT;
	typedef struct AFC_RULE
	{
		const char* Name;
		int ArgNum;
		int RetId;
	} AFC_RULE;

	AF_EXPORT AFC_HOPT AFC_CreateOptionProcessor();
	AF_EXPORT void AFC_DestroyOptionProcessor(AFC_HOPT hOpt);
	AF_EXPORT void AFC_BindOption(AFC_HOPT hOpt, int argc, char* argv[]);
	AF_EXPORT int AFC_ProcOption(AFC_HOPT hOpt, AFC_RULE* RuleList);
	AF_EXPORT int AFC_GetOption(AFC_HOPT hOpt, char* buffer, int bufsize); // bool

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BASEOPT_H
