#pragma once

#ifndef GENSHINIMPACTAPI_H
#define GENSHINIMPACTAPI_H

#ifdef GIAPI_BUILD
#define GIAPI_EXPORT	__declspec(dllexport)
#else
#define GIAPI_EXPORT	__declspec(dllimport)
#endif // GIAPI_BUILD

#ifdef __cplusplus

#include <vcruntime.h>
#include <objbase.h>

#if _HAS_CXX17

#include <string>
#include <vector>
#include <filesystem>

#include <json.hpp>

namespace GIAPI
{
	using string = std::string;
	using strlist = std::vector<std::string>;
	using wstring = std::wstring;
	using wstrlist = std::vector<std::string>;
	using path = std::filesystem::path;
	using json = nlohmann::json;

	enum Server
	{
		UNKNOWN,
		CNREL_OFFICIAL,
		CNREL_BILIBILI,
		OSREL_GLOBAL
	};

	enum Language
	{
		zh_CN = 0x1,
		en_US = 0x2,
		ja_JP = 0x4,
		ko_KR = 0x8
	};

	enum ErrorCode
	{
		Success,
		UnknownError,
		ResourceIndexNotLoaded,
		LocalMetadataNotLoaded,
		NotInstalled,
		AlreadyInstalled,
		AlreadyLatest,
		ServerIdNotSet,
		LanguageIdNotSet,
		NeedReinstall,
		PredownloadNotSupported,
		TargetPathNotSupported
	};

	class GIAPI_EXPORT Manager
	{
	public:
		Manager();
		~Manager();
		Manager(const Manager&) = delete;
		Manager& operator=(const Manager&) = delete;
		ErrorCode ResourceIndexUrl(Server ServerId, string& ReturnUrl) const;
		ErrorCode LoadResourceIndex(path ResourcePath);
		ErrorCode LoadLocalMetadata(path MetadataPath);
		ErrorCode GetLocalGameServer(Server& ReturnServerId) const;
		ErrorCode GetInstallPackageUrl(int Language, strlist& ReturnList) const;
		ErrorCode GetPreInstallPackageUrl(int Language, strlist& ReturnList) const;
		ErrorCode GetUpdatePackageUrl(strlist& ReturnList) const;
		ErrorCode GetPreUpdatePackageUrl(strlist& ReturnList) const;
		bool StatInstalled() const;
		bool StatLatest(bool PreVer = false) const;
		bool StatPreDownload() const;
		ErrorCode Install(strlist FileList, string Path, Server ServerId, int LanguageId);
		ErrorCode PreInstall(strlist FileList, string Path, Server ServerId, int LanguageId);
		ErrorCode Update(strlist FileList);
		ErrorCode PreUpdate(strlist FileList);
		ErrorCode Uninstall();
		ErrorCode Launch() const;
	private:
		json ResourceIndex;
		json LocalMetadata;
		path MetadataPath;
		bool ResourceIndexStat;
		bool LocalMetadataStat;
		void FlushMetadata() const;
	};
}

#else
#error The minimum version of the GenshinImpactAPI is C++17.
#endif // _HAS_CXX17

#endif // __cplusplus

#endif // !GENSHINIMPACTAPI_H
