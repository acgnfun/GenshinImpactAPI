#pragma once

#ifndef OPTPROC_H
#define OPTPROC_H

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

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus

#include <string>
#include <vector>

namespace afc
{
	using rule = AFC_RULE;
	using strlist = std::vector<std::string>;

	class AF_EXPORT optobj
	{
	public:
		optobj();
		optobj(int argc, char* argv[]);
		~optobj();
		optobj(const optobj&) = delete;
		optobj& operator=(const optobj&) = delete;
		void bindopt(int argc, char* argv[]);
		int procopt(rule* rulelist);
		bool getopt(char* buffer, int bufsize);
		bool getopt(std::string& buffer);
		void clear();
	private:
		strlist optbuffer;
		char** baseaddr;
		int argc;
		int optid;
	};
}

#endif // __cplusplus

#endif // !OPTPROC_H
