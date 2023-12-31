#pragma once

#ifndef BASEDOWNLOAD_H
#define BASEDOWNLOAD_H

#include "BaseLibrary.h"

#ifdef __cplusplus

#include <string>
#include <filesystem>

namespace afc
{
	typedef bool(*download_callback)(uintmax_t total_bytes, uintmax_t download_bytes, uintmax_t speed_bytes);

	AF_EXPORT bool download(std::string url, std::filesystem::path path, download_callback callback = nullptr);
}

#endif // __cplusplus

#endif // !BASEDOWNLOAD_H
