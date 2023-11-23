#include <iostream>
#include "../GenshinImpactAPI/GenshinImpactAPI.h"

int main(int argc, char* argv[])
{
	GIAPI::Manager Man;
	Man.LoadResourceIndex("ResourceIndex.json");
	Man.LoadLocalMetadata("Metadata.json");
	CoInitialize(nullptr); // 初始化COM组件，进行该动作后安装时将在桌面创建快捷方式
	Man.Install(
		{
			"GenshinImpact_x.x.x.zip.001",
			"Audio_xx_x.x.x.zip"
		},
		"目标（安装）目录",
		GIAPI::OSREL_GLOBAL, // 指示安装文件来源
		GIAPI::zh_CN // 指示安装文件语言
	);
	CoUninitialize();
	return 0;
}
