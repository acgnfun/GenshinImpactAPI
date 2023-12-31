#pragma once

#ifndef OPTPROC_H
#define OPTPROC_H

#include "BaseLibrary.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#include "BaseOpt.h"
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
