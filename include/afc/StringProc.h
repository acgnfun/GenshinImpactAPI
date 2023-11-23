#pragma once

#ifndef AFSTRING_H
#define AFSTRING_H

#include "BaseLibrary.h"

#ifdef __cplusplus

#include <string>

namespace afc
{
	AF_EXPORT std::string convert_string(std::wstring string);
	AF_EXPORT std::wstring convert_string(std::string string);
	AF_EXPORT bool match_head(std::string string, std::string pattern);
	AF_EXPORT bool match_tail(std::string string, std::string pattern);
}

#endif // __cplusplus

#endif // !AFSTRING_H
