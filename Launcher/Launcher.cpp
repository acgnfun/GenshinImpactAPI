// Launcher.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Launcher.h"

#define MAX_LOADSTRING 100

#define URL_CONTENT_OFFICIAL	"https://hk4e-launcher-static.mihoyo.com/hk4e_cn/mdk/launcher/api/content?filter_adv=true&key=eYd89JmJ&language=zh-cn&launcher_id=18"
#define URL_CONTENT_BILIBILI	"https://hk4e-launcher-static.mihoyo.com/hk4e_cn/mdk/launcher/api/content?filter_adv=true&key=KAtdSsoQ&language=zh-cn&launcher_id=17"
#define URL_CONTENT_GLOBAL		"https://hk4e-launcher-static.hoyoverse.com/hk4e_global/mdk/launcher/api/content?filter_adv=true&key=gcStgarh&language=zh-cn&launcher_id=10"

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

bool ThreadRunning = false;
std::wstring InstallPath;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Input(HWND, UINT, WPARAM, LPARAM);

bool PositionInRectangle(UINT x, UINT y, D2D1_RECT_F Rectangle);
void InstallGame();
void UpdateGame();
void PreUpdateGame();
void UninstallGame();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAUNCHER, szWindowClass, MAX_LOADSTRING);

	HANDLE hMutex = CreateMutexW(nullptr, false, szWindowClass);
	if (!hMutex || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hWnd = FindWindowW(szWindowClass, nullptr);
		SetForegroundWindow(hWnd);
		return 1;
	}

	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAUNCHER));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CloseHandle(hMutex);

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAUNCHER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAUNCHER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_LAUNCHER));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateCentralWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		1280, 720, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

enum BtnType
{
	Btn_Install,
	Btn_Update,
	Btn_Launch
} tBtn;

DXADevice Device;
DXAContext Context;
DXAWICFactory WICFactory;

ID2D1Bitmap* pBackground = nullptr;
ID2D1Bitmap* pBtnMain = nullptr;

ID2D1Bitmap* pBitmapBuffer = nullptr;

RECT WndRect;
D2D1_RECT_F MainRect;
D2D1_RECT_F BtnRect;

GIAPI::Manager Manager;
GIAPI::Language gLang;
GIAPI::Server sId;

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		LANGID Lang = GetUserDefaultUILanguage();
		if (Lang & LANG_CHINESE)
			gLang = GIAPI::zh_CN;
		else if (Lang & LANG_ENGLISH)
			gLang = GIAPI::en_US;
		else if (Lang & LANG_JAPANESE)
			gLang = GIAPI::ja_JP;
		else if (Lang & LANG_KOREAN)
			gLang = GIAPI::ko_KR;
		if (!std::filesystem::exists(afc::program_dir_path() / "Config"))
			std::filesystem::create_directory(afc::program_dir_path() / "Config");
		HRESULT hr = CoInitialize(nullptr);
		Device.Initialize();
		Context.Initialize(&Device, hWnd);
		WICFactory.Initialize();
		hr = DXACreateBitmap(WICFactory, Context, hInst, MAKEINTRESOURCEW(IDB_BACKGROUND), L"PNG", &pBackground);
		Manager.LoadLocalMetadata(afc::program_dir_path() / "Config" / "Metadata.json");
		if (Manager.LoadResourceIndex(afc::program_dir_path() / "Config" / "Resource.json") != GIAPI::Success)
		{
			std::string ResourceUrl;
			sId = GIAPI::CNREL_OFFICIAL;
			Manager.ResourceIndexUrl(sId, ResourceUrl);
			afc::download(ResourceUrl, (afc::program_dir_path() / "Config" / "Resource.json").string());
			if (Manager.LoadResourceIndex(afc::program_dir_path() / "Config" / "Resource.json") != GIAPI::Success)
			{
				DestroyWindow(hWnd);
				break;
			}
		}
		int nBtnId = 0;
		if (!Manager.StatInstalled())
		{
			tBtn = Btn_Install;
			nBtnId = IDB_INSTALL;
		}
		else if (!Manager.StatLatest())
		{
			tBtn = Btn_Update;
			nBtnId = IDB_UPDATE;
		}
		else
		{
			tBtn = Btn_Launch;
			nBtnId = IDB_LAUNCH;
		}
		hr = DXACreateBitmap(WICFactory, Context, hInst, MAKEINTRESOURCEW(nBtnId), L"PNG", &pBtnMain);
		hr = DXACreateBitmap(WICFactory, Context, (afc::program_dir_path() / L"Assets" / L"Background.png").wstring().c_str(), &pBitmapBuffer);
		if (!SUCCEEDED(hr) && afc::download(URL_CONTENT_OFFICIAL, (afc::program_dir_path() / L"Config" / L"Content.json").string()))
		{
			nlohmann::json content;
			std::fstream file(afc::program_dir_path() / L"Config" / L"Content.json");
			if (file.is_open())
			{
				try
				{
					file >> content;
				}
				catch (...) {}
				file.close();
				try
				{
					if (!std::filesystem::exists(afc::program_dir_path() / "Assets"))
						std::filesystem::create_directory(afc::program_dir_path() / "Assets");
					std::string url = content["data"]["adv"]["background"];
					if (afc::download(url, (afc::program_dir_path() / L"Assets" / L"Background.png").string()))
					{
						hr = DXACreateBitmap(WICFactory, Context, (afc::program_dir_path() / L"Assets" / L"Background.png").wstring().c_str(), &pBitmapBuffer);
					}
				}
				catch (...) {}
			}
		}
		if (SUCCEEDED(hr))
		{
			if (pBackground) pBackground->Release();
			pBackground = pBitmapBuffer;
			pBitmapBuffer = nullptr;
		}
		std::string instpath;
		if (Manager.GetInstallPath(instpath) == GIAPI::Success)
			InstallPath = afc::convert_string(instpath);
		else
			InstallPath = L"C:\\Program Files\\Genshin Impact Game";
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_INSTALL:
			if (ThreadRunning) break;
			std::thread(InstallGame).detach();
			break;
		case IDM_UPDATE:
			if (ThreadRunning) break;
			std::thread(UpdateGame).detach();
			break;
		case IDM_PREUPDATE:
			if (ThreadRunning) break;
			std::thread(PreUpdateGame).detach();
			break;
		case IDM_UNINSTALL:
			if (ThreadRunning) break;
			std::thread(UninstallGame).detach();
			break;
		case IDM_LAUNCH:
			if (ThreadRunning) break;
			Manager.Launch();
			break;
		case IDM_INSTPOS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_INPUT), hWnd, Input);
			break;
		case IDM_SERVER_OFFICIAL:
		{
			std::string ResourceUrl;
			sId = GIAPI::CNREL_OFFICIAL;
			Manager.ResourceIndexUrl(sId, ResourceUrl);
			if (afc::download(ResourceUrl, (afc::program_dir_path() / "Config" / "Resource.json").string()))
				Manager.LoadResourceIndex(afc::program_dir_path() / "Config" / "Resource.json");
			if (afc::download(URL_CONTENT_OFFICIAL, (afc::program_dir_path() / L"Config" / L"Content.json").string()))
			{
				nlohmann::json content;
				std::fstream file(afc::program_dir_path() / L"Config" / L"Content.json");
				if (file.is_open())
				{
					try
					{
						file >> content;
					}
					catch (...) {}
					file.close();
					try
					{
						if (!std::filesystem::exists(afc::program_dir_path() / "Assets"))
							std::filesystem::create_directory(afc::program_dir_path() / "Assets");
						std::string url = content["data"]["adv"]["background"];
						if (pBackground) pBackground->Release();
						pBackground = nullptr;
						if (afc::download(url, (afc::program_dir_path() / L"Assets" / L"Background.png").string()))
						{
							HRESULT hr = DXACreateBitmap(WICFactory, Context, (afc::program_dir_path() / L"Assets" / L"Background.png").wstring().c_str(), &pBitmapBuffer);
							if (SUCCEEDED(hr))
							{
								if (pBackground) pBackground->Release();
								pBackground = pBitmapBuffer;
								pBitmapBuffer = nullptr;
							}
						}
					}
					catch (...) {}
				}
			}
			InvalidateRect(hWnd, nullptr, false);
			UpdateWindow(hWnd);
		}
		break;
		case IDM_SERVER_BILIBILI:
		{
			std::string ResourceUrl;
			sId = GIAPI::CNREL_BILIBILI;
			Manager.ResourceIndexUrl(sId, ResourceUrl);
			if (afc::download(ResourceUrl, (afc::program_dir_path() / "Config" / "Resource.json").string()))
				Manager.LoadResourceIndex(afc::program_dir_path() / "Config" / "Resource.json");
			if (afc::download(URL_CONTENT_BILIBILI, (afc::program_dir_path() / L"Config" / L"Content.json").string()))
			{
				nlohmann::json content;
				std::fstream file(afc::program_dir_path() / L"Config" / L"Content.json");
				if (file.is_open())
				{
					try
					{
						file >> content;
					}
					catch (...) {}
					file.close();
					try
					{
						if (!std::filesystem::exists(afc::program_dir_path() / "Assets"))
							std::filesystem::create_directory(afc::program_dir_path() / "Assets");
						std::string url = content["data"]["adv"]["background"];
						if (pBackground) pBackground->Release();
						pBackground = nullptr;
						if (afc::download(url, (afc::program_dir_path() / L"Assets" / L"Background.png").string()))
						{
							HRESULT hr = DXACreateBitmap(WICFactory, Context, (afc::program_dir_path() / L"Assets" / L"Background.png").wstring().c_str(), &pBitmapBuffer);
							if (SUCCEEDED(hr))
							{
								if (pBackground) pBackground->Release();
								pBackground = pBitmapBuffer;
								pBitmapBuffer = nullptr;
							}
						}
					}
					catch (...) {}
				}
			}
			InvalidateRect(hWnd, nullptr, false);
			UpdateWindow(hWnd);
		}
		break;
		case IDM_SERVER_GLOBAL:
		{
			std::string ResourceUrl;
			sId = GIAPI::OSREL_GLOBAL;
			Manager.ResourceIndexUrl(sId, ResourceUrl);
			if (afc::download(ResourceUrl, (afc::program_dir_path() / "Config" / "Resource.json").string()))
				Manager.LoadResourceIndex(afc::program_dir_path() / "Config" / "Resource.json");
			if (afc::download(URL_CONTENT_GLOBAL, (afc::program_dir_path() / L"Config" / L"Content.json").string()))
			{
				nlohmann::json content;
				std::fstream file(afc::program_dir_path() / L"Config" / L"Content.json");
				if (file.is_open())
				{
					try
					{
						file >> content;
					}
					catch (...) {}
					file.close();
					try
					{
						if (!std::filesystem::exists(afc::program_dir_path() / "Assets"))
							std::filesystem::create_directory(afc::program_dir_path() / "Assets");
						std::string url = content["data"]["adv"]["background"];
						if (pBackground) pBackground->Release();
						pBackground = nullptr;
						if (afc::download(url, (afc::program_dir_path() / L"Assets" / L"Background.png").string()))
						{
							HRESULT hr = DXACreateBitmap(WICFactory, Context, (afc::program_dir_path() / L"Assets" / L"Background.png").wstring().c_str(), &pBitmapBuffer);
							if (SUCCEEDED(hr))
							{
								if (pBackground) pBackground->Release();
								pBackground = pBitmapBuffer;
								pBitmapBuffer = nullptr;
							}
						}
					}
					catch (...) {}
				}
			}
			InvalidateRect(hWnd, nullptr, false);
			UpdateWindow(hWnd);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		Context.BeginDraw();
		Context.Clear();
		if (pBackground)
			Context.FillBitmap(
				pBackground,
				MainRect
			);
		if (pBtnMain)
			Context.FillBitmap(
				pBtnMain,
				BtnRect
			);
		Context.EndDraw();
	}
	break;
	case WM_LBUTTONDOWN:
		if (PositionInRectangle(LOWORD(lParam), HIWORD(lParam), BtnRect))
		{
			switch (tBtn)
			{
			case Btn_Install:
				PostMessageW(hWnd, WM_COMMAND, IDM_INSTALL, 0);
				break;
			case Btn_Update:
				PostMessageW(hWnd, WM_COMMAND, IDM_UPDATE, 0);
				break;
			case Btn_Launch:
				PostMessageW(hWnd, WM_COMMAND, IDM_LAUNCH, 0);
				break;
			default:
				MessageBeep(MB_ICONERROR);
				DestroyWindow(hWnd);
				break;
			}
		}
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &WndRect);
		MainRect.left = WndRect.left;
		MainRect.top = WndRect.top;
		MainRect.right = WndRect.right;
		MainRect.bottom = WndRect.bottom;
		BtnRect.left = WndRect.right * 0.8;
		BtnRect.top = WndRect.bottom * 0.8;
		BtnRect.right = WndRect.right * 0.95;
		BtnRect.bottom = WndRect.bottom * 0.9;
		break;
	case WM_ERASEBKGND:
		return FALSE;
	case WM_DESTROY:
		WICFactory.Uninitialize();
		Context.Uninitialize();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hEdit = GetDlgItem(hDlg, IDC_INPUT_EDIT);
		SetWindowTextW(hEdit, InstallPath.c_str());
	}
	return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK)
			{
				WCHAR Buffer[512] = { 0 };
				HWND hEdit = GetDlgItem(hDlg, IDC_INPUT_EDIT);
				GetWindowTextW(hEdit, Buffer, 512);
				InstallPath = Buffer;
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

bool PositionInRectangle(UINT x, UINT y, D2D1_RECT_F Rectangle)
{
	return x > Rectangle.left && x < Rectangle.right && y > Rectangle.top && y < Rectangle.bottom;
}

void InstallGame()
{
	ThreadRunning = true;
	GIAPI::urllist list;
	GIAPI::strlist flist;
	Manager.GetInstallPackageUrl(gLang, list);
	if (!std::filesystem::exists(afc::program_dir_path() / "Cache"))
		std::filesystem::create_directory(afc::program_dir_path() / "Cache");
	for (auto i : list)
	{
		if (std::filesystem::exists(afc::program_dir_path() / "Cache" / i.filename))
		{
			flist.push_back((afc::program_dir_path() / "Cache" / i.filename).string());
			continue;
		}
		if (afc::download(i.url, (afc::program_dir_path() / "Cache" / (i.filename + ".tmp")).string()))
		{
			std::filesystem::rename(afc::program_dir_path() / "Cache" / (i.filename + ".tmp"), afc::program_dir_path() / "Cache" / i.filename);
			flist.push_back((afc::program_dir_path() / "Cache" / i.filename).string());
		}
	}
	CoInitialize(nullptr);
	Manager.Install(flist, "D:\\Program Files\\Genshin Impact Game 2", sId, gLang);
	CoUninitialize();
	ThreadRunning = false;
}

void UpdateGame()
{
	ThreadRunning = true;
	GIAPI::urllist list;
	GIAPI::strlist flist;
	Manager.GetUpdatePackageUrl(list);
	if (!std::filesystem::exists(afc::program_dir_path() / "Cache"))
		std::filesystem::create_directory(afc::program_dir_path() / "Cache");
	for (auto i : list)
	{
		if (std::filesystem::exists(afc::program_dir_path() / "Cache" / i.filename))
		{
			flist.push_back((afc::program_dir_path() / "Cache" / i.filename).string());
			continue;
		}
		if (afc::download(i.url, (afc::program_dir_path() / "Cache" / (i.filename + ".tmp")).string()))
		{
			std::filesystem::rename(afc::program_dir_path() / "Cache" / (i.filename + ".tmp"), afc::program_dir_path() / "Cache" / i.filename);
			flist.push_back((afc::program_dir_path() / "Cache" / i.filename).string());
		}
	}
	Manager.Update(flist);
	ThreadRunning = false;
}

void PreUpdateGame()
{
	ThreadRunning = true;
	GIAPI::urllist list;
	GIAPI::strlist flist;
	Manager.GetPreUpdatePackageUrl(list);
	if (!std::filesystem::exists(afc::program_dir_path() / "Cache"))
		std::filesystem::create_directory(afc::program_dir_path() / "Cache");
	for (auto i : list)
	{
		if (std::filesystem::exists(afc::program_dir_path() / "Cache" / i.filename))
		{
			flist.push_back((afc::program_dir_path() / "Cache" / i.filename).string());
			continue;
		}
		if (afc::download(i.url, (afc::program_dir_path() / "Cache" / (i.filename + ".tmp")).string()))
		{
			std::filesystem::rename(afc::program_dir_path() / "Cache" / (i.filename + ".tmp"), afc::program_dir_path() / "Cache" / i.filename);
			flist.push_back((afc::program_dir_path() / "Cache" / i.filename).string());
		}
	}
	Manager.PreUpdate(flist);
	ThreadRunning = false;
}

void UninstallGame()
{
	ThreadRunning = true;
	Manager.Uninstall();
	ThreadRunning = false;
}
