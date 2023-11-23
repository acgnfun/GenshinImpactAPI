#include <iostream>
#include "../GenshinImpactAPI/GenshinImpactAPI.h"

int main(int argc, char* argv[])
{
	GIAPI::Manager Man;
	Man.LoadResourceIndex("ResourceIndex.json");
	Man.LoadLocalMetadata("Metadata.json");
	CoInitialize(nullptr); // ��ʼ��COM��������иö�����װʱ�������洴����ݷ�ʽ
	Man.Install(
		{
			"GenshinImpact_x.x.x.zip.001",
			"Audio_xx_x.x.x.zip"
		},
		"Ŀ�꣨��װ��Ŀ¼",
		GIAPI::OSREL_GLOBAL, // ָʾ��װ�ļ���Դ
		GIAPI::zh_CN // ָʾ��װ�ļ�����
	);
	CoUninitialize();
	return 0;
}
