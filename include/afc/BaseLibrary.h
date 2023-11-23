#pragma once

#ifndef BASELIBRARY_H
#define BASELIBRARY_H

#include <stdint.h>

#ifdef AF_BUILD
#define AF_EXPORT	__declspec(dllexport)
#else
#define AF_EXPORT	__declspec(dllimport)
#endif // AF_BUILD

#endif // !BASELIBRARY_H
