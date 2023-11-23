# GenshinImpactAPI

## 注意

- 代码中几乎没有注释，此处列出了API使用方法

## 详细介绍

- 在工程中引入lib文件和dll文件即可使用API
- 提供了一个GIAPI::Manager类，包含相关API
- 实例化Manager类即可使用相关接口
- 可以同时在一个程序中实例化多个类以同时控制计算机上的多个安装位置

## 使用方法

- ResourceIndexUrl方法：获取最新版本的安装文件清单Url，其中ServerId指示清单的来源
	- CNREL_OFFICIAL 官服
	- CNREL_BILIBILI B服
	- OSREL_GLLOBAL 国际服
- LoadResourceIndex方法：将下载到本地的清单文件加载到内存（如果使用关于安装、更新、预下载等API则必须加载清单文件）
- LoadLocalMetadata方法：加载或创建（如果不存在）本地游戏元数据文件，其中包含了本地游戏文件的安装位置信息，版本信息，语言等（必须加载！！！）
- GetLocalGameServer方法：获取本地游戏安装的服务器来源
- GetInstallPackageUrl方法：获取当前版本游戏安装文件的Url列表，其中Language指示安装文件的语言
	- zh-CN
	- en_US
	- ja_JP
	- ko_KR
	- 以上常量可以做或`|`运算以达到同时下载安装多个语言包的目的，如：zh_CN | en_US 即同时获取中英文语言包
- GetPreInstallPackageUrl方法：获取预下载版本的安装文件Url列表（如果可用）
- GetUpdatePackageUrl方法：获取更新到当前版本所需的更新文件的Url列表，如果本地版本过于久远会返回错误代码`NeedReinstall`，则需要卸载当前版本重新安装
- GetPreUpdatePackageUrl方法：获取更新到预下载版本所需的更新文件的Url列表
- StatInstalled方法：从元数据查看本地游戏文件的安装状态
- StatLatest方法：从元数据查看本地游戏文件的最新状态，当PreVer设置为true时搜索预下载版本，如果预下载不可用则返回false
- StatPreDownload方法：检测当前是否支持预下载
- Install方法：提供FileList安装文件列表（通过之前获取的Url下载），Path安装位置，ServerId安装文件服务器来源，LanguangeId安装文件语言

## 尚未完成