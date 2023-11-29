#include "../GenshinImpactAPI/GenshinImpactAPI.h"
#include <iostream>
#include <afc/OptProc.h>
#include <afc/BaseDownload.h>

static std::vector<std::pair<std::string, std::string>> DownloadPairs;
static std::string ResourcePath;
static std::string MetadataPath;
static std::string InstallPath;
static std::string DownloadPath;
static std::vector<std::string> Packs;
static bool TagPreVer = false;
static bool TagDownoadResource = false;
static bool TagRILoad = false;
static bool TagMTLoad = false;
static bool TagPrint = false;
static bool TagPrintdlinfo = false;
static bool TagPrintupinfo = false;
static bool TagInstall = false;
static bool TagUpdate = false;
static bool TagUninstall = false;
static bool TagLaunch = false;
static int LanguageId = 0;
static GIAPI::Server ServerId = GIAPI::UNKNOWN;

static afc::rule rulist[] = {
	{ "help",      0, 1 },
	{ "download",  2, 2 },
	{ "resource",  1, 3 },
	{ "metadata",  1, 4 },
	{ "print",     0, 5 },
	{ "dlinfo",    0, 6 },
	{ "upinfo",    0, 7 },
	{ "install",   1, 8 },
	{ "uninstall", 0, 9 },
	{ "update",    0, 10 },
	{ "launch",    0, 11 },
	{ "pack",      1, 12 },
	{ "zh_CN",     0, 13 },
	{ "en_US",     0, 14 },
	{ "ja_JP",     0, 15 },
	{ "ko_KR",     0, 16 },
	{ "cnrel",     0, 17 },
	{ "cnrel2",    0, 18 },
	{ "osrel",     0, 19 },
	{ "download-resource", 1, 20},
	{ "prever",    0, 21},
	{ nullptr,     0, 0 }
};

static void help()
{
	std::cout
		<< "GenshinImpactAPI_Example v0.1.0 (C) 2023 acgnfun\n"
		<< "    -help                     show this help.\n"
		<< "    -download <url> <path>    download url to path.\n"
		<< "    -download-resource <path> download resource to path.\n"
		<< "        -cnrel/-cnrel2/-osrel specify the source of the resource file server.\n"
		<< "            cnrel:official server, cnrel2:bilibili server, osrel: global server.\n"
		<< "    -resource <path>          load resource index.\n"
		<< "    -metadata <path>          load local game metadata.\n"
		<< "    -print                    print messages.\n"
		<< "        -dlinfo               print install packages' url list.\n"
		<< "            -zh_CN            with voice pack(Chinese).\n"
		<< "            -en_US            with voice pack(English).\n"
		<< "            -ja_JP            with voice pack(Japanese).\n"
		<< "            -ko_KR            with voice pack(Korean).\n"
		<< "        -upinfo               print update packages' url list.\n"
		<< "        -prever               switch to pre-download information.\n"
		<< "    -install <path>           install packages to path.\n"
		<< "        -pack <path>          load install package.\n"
		<< "        -zh_CN                install with voice pack(Chinese).\n"
		<< "        -en_US                install with voice pack(English).\n"
		<< "        -ja_JP                install with voice pack(Japanese).\n"
		<< "        -ko_KR                install with voice pack(Korean).\n"
		<< "        -cnrel/-cnrel2/-osrel specify the source of the installation file server.\n"
		<< "            cnrel:official server, cnrel2:bilibili server, osrel: global server.\n"
		<< "    -update                   update local game.\n"
		<< "        -pack <path>          load update package.\n"
		<< "    -uninstall                uninstall game.\n"
		<< "    -launch                   launch game." << std::endl;
}

static bool printerror();
static bool run();

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		help();
		return 1;
	}
	std::string temp1, temp2;
	afc::optobj hopt(argc, argv);
	while (true)
	{
		switch (hopt.procopt(rulist))
		{
		case AFC_OPT_NOT_FOUND:
		case 1:
			help();
			return 1;
		case 2:
			hopt.getopt(temp1);
			hopt.getopt(temp2);
			if (temp1.empty() || temp2.empty())
				break;
			DownloadPairs.push_back({ temp1, temp2 });
			break;
		case 3:
			hopt.getopt(ResourcePath);
			if (!ResourcePath.empty()) TagRILoad = true;
			break;
		case 4:
			hopt.getopt(MetadataPath);
			if (!MetadataPath.empty()) TagMTLoad = true;
			break;
		case 5:
			TagPrint = true;
			break;
		case 6:
			if (TagPrint) TagPrintdlinfo = true;
			break;
		case 7:
			if (TagPrint) TagPrintupinfo = true;
			break;
		case 8:
			hopt.getopt(InstallPath);
			if (!InstallPath.empty()) TagInstall = true;
			break;
		case 9:
			TagUninstall = true;
			break;
		case 10:
			TagUpdate = true;
			break;
		case 11:
			TagLaunch = true;
			break;
		case 12:
			hopt.getopt(temp1);
			if (!temp1.empty()) Packs.push_back(temp1);
			break;
		case 13:
			LanguageId |= GIAPI::zh_CN;
			break;
		case 14:
			LanguageId |= GIAPI::en_US;
			break;
		case 15:
			LanguageId |= GIAPI::ja_JP;
			break;
		case 16:
			LanguageId |= GIAPI::ko_KR;
			break;
		case 17:
			ServerId = GIAPI::CNREL_OFFICIAL;
			break;
		case 18:
			ServerId = GIAPI::CNREL_BILIBILI;
			break;
		case 19:
			ServerId = GIAPI::OSREL_GLOBAL;
			break;
		case 20:
			hopt.getopt(DownloadPath);
			if (!DownloadPath.empty()) TagDownoadResource = true;
			break;
		case 21:
			if (TagPrint || TagInstall || TagUpdate)
				TagPreVer = true;
			break;
		case AFC_OPT_ERROR:
			if (printerror()) // check input commandline options' error.
				return 1;
			if (!run()) // if have no error, run proc function.
				return 1;
			return 0;
		}
	}
	return 0;
}

bool printerror()
{
	bool error = false;
	if (TagDownoadResource && ServerId == GIAPI::UNKNOWN)
	{
		std::cerr << "the server must be specified." << std::endl;
		error = true;
	}
	if (TagPrint || TagInstall || TagUninstall || TagUpdate || TagLaunch)
	{
		if (!TagRILoad)
		{
			std::cerr << "resource index file not loaded." << std::endl;
			error = true;
		}
		if (!TagMTLoad)
		{
			std::cerr << "metadata file not loaded." << std::endl;
			error = true;
		}
	}
	if (TagPrint && !(TagPrintdlinfo || TagPrintupinfo))
	{
		std::cerr << "printing information is not prescribed." << std::endl;
		error = true;
	}
	if ((TagPrintdlinfo || TagInstall) && LanguageId == 0)
	{
		std::cerr << "at least one language needs to be selected." << std::endl;
		error = true;
	}
	if (TagInstall && ServerId == GIAPI::UNKNOWN)
	{
		std::cerr << "the server must be specified." << std::endl;
		error = true;
	}
	int counter = 0;
	if (TagInstall) counter++;
	if (TagUninstall) counter++;
	if (TagUpdate) counter++;
	if (counter > 1)
	{
		std::cerr << "the '-install', '-uninstall' and '-update' options cannot be enabled at the same time." << std::endl;
		error = true;
	}
	if ((TagInstall || TagUpdate) && Packs.empty())
	{
		std::cerr << "the installation/update package is not specified." << std::endl;
		error = true;
	}
	return error;
}

bool run() // proc function.
{
	try
	{
		GIAPI::Manager Man;
		if (TagDownoadResource)
		{
			std::string DownloadUrl;
			Man.ResourceIndexUrl(ServerId, DownloadUrl);
			AFC_DownloadA(DownloadUrl.c_str(), DownloadPath.c_str());
		}
		for (auto i : DownloadPairs)
		{
			AFC_DownloadA(i.first.c_str(), i.second.c_str());
		}
		std::vector<std::string> list;
		if (TagRILoad)
			Man.LoadResourceIndex(ResourcePath);
		if (TagMTLoad)
			Man.LoadLocalMetadata(MetadataPath);
		bool Pre = Man.StatPreDownload();
		if (TagPreVer && !Pre)
		{
			std::cerr << "pre-downloads are not currently supported." << std::endl;
			return false;
		}
		if (TagPrintdlinfo)
		{
			if (TagPreVer)
				Man.GetPreInstallPackageUrl(LanguageId, list);
			else
				Man.GetInstallPackageUrl(LanguageId, list);
			std::cout << "install packages:" << std::endl;
			for (auto i : list)
				std::cout << i << std::endl;
		}
		if (TagPrintupinfo)
		{
			if (TagPreVer)
				Man.GetPreUpdatePackageUrl(list);
			else
				Man.GetUpdatePackageUrl(list);
			std::cout << "update packages:" << std::endl;
			for (auto i : list)
				std::cout << i << std::endl;
		}
		if (TagInstall)
		{
			CoInitialize(nullptr);
			if (TagPreVer)
				Man.Install(Packs, InstallPath, ServerId, LanguageId);
			else
				Man.PreInstall(Packs, InstallPath, ServerId, LanguageId);
			CoUninitialize();
		}
		else if (TagUpdate)
		{
			if (TagPreVer)
				Man.PreUpdate(Packs);
			else
				Man.Update(Packs);
		}
		else if (TagUninstall)
		{
			Man.Uninstall();
		}
		if (TagLaunch)
		{
			Man.Launch();
		}
	}
	catch (...) { return false; }
	return true;
}
