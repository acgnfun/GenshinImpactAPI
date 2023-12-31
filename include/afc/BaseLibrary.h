#pragma once

#ifndef BASELIBRARY_H
#define BASELIBRARY_H

#include <stdint.h>

#ifdef AF_BUILD
#define AF_EXPORT	__declspec(dllexport)
#else
#define AF_EXPORT	__declspec(dllimport)
#endif // AF_BUILD

#ifdef AF_STATICLIB
#undef AF_EXPORT
#define AF_EXPORT
#endif // AF_STATICLIB

#endif // !BASELIBRARY_H
