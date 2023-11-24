# GenshinImpactAPI

## ע��

- �����м���û��ע�ͣ��˴��г���APIʹ�÷���

## ��ϸ����

- �ڹ���������lib�ļ���dll�ļ�����ʹ��API
- �ṩ��һ��GIAPI::Manager�࣬�������API
- ʵ����Manager�༴��ʹ����ؽӿ�
- ����ͬʱ��һ��������ʵ�����������ͬʱ���Ƽ�����ϵĶ����װλ��

## ʹ�÷���

- ResourceIndexUrl��������ȡ���°汾�İ�װ�ļ��嵥Url������ServerIdָʾ�嵥����Դ
	- CNREL_OFFICIAL �ٷ�
	- CNREL_BILIBILI B��
	- OSREL_GLLOBAL ���ʷ�
- LoadResourceIndex�����������ص����ص��嵥�ļ����ص��ڴ棨���ʹ�ù��ڰ�װ�����¡�Ԥ���ص�API���������嵥�ļ���
- LoadLocalMetadata���������ػ򴴽�����������ڣ�������ϷԪ�����ļ������а����˱�����Ϸ�ļ��İ�װλ����Ϣ���汾��Ϣ�����Եȣ�������أ�������
- GetLocalGameServer��������ȡ������Ϸ��װ�ķ�������Դ
- GetInstallPackageUrl��������ȡ��ǰ�汾��Ϸ��װ�ļ���Url�б�����Languageָʾ��װ�ļ�������
	- zh-CN
	- en_US
	- ja_JP
	- ko_KR
	- ���ϳ�����������`|`�����Դﵽͬʱ���ذ�װ������԰���Ŀ�ģ��磺zh_CN | en_US ��ͬʱ��ȡ��Ӣ�����԰�
- GetPreInstallPackageUrl��������ȡԤ���ذ汾�İ�װ�ļ�Url�б�������ã�
- GetUpdatePackageUrl��������ȡ���µ���ǰ�汾����ĸ����ļ���Url�б�������ذ汾���ھ�Զ�᷵�ش������`NeedReinstall`������Ҫж�ص�ǰ�汾���°�װ
- GetPreUpdatePackageUrl��������ȡ���µ�Ԥ���ذ汾����ĸ����ļ���Url�б�
- StatInstalled��������Ԫ���ݲ鿴������Ϸ�ļ��İ�װ״̬
- StatLatest��������Ԫ���ݲ鿴������Ϸ�ļ�������״̬����PreVer����Ϊtrueʱ����Ԥ���ذ汾�����Ԥ���ز������򷵻�false
- StatPreDownload��������⵱ǰ�Ƿ�֧��Ԥ����
- Install��������װ��Ϸ�ļ�����Ҫ�ṩFileList��װ�ļ��б�ͨ��֮ǰ��ȡ��Url���أ���Path��װλ�ã�ServerId��װ�ļ���������Դ��LanguangeId��װ�ļ�����
- PreInstall������ͬ�ϣ���ʹ��Ԥ�����ļ���Ԥ���ط�ʽ��ȡ���ļ�ֻ��ͨ��Ԥ����API��װ����£���������ͨģʽ���ã�APIͬ��
- Update������������Ϸ����Ҫ�ṩ�����ļ��б�ͨ��֮ǰ��ȡ��Url���أ�
- PreUpdate������ͬ�ϣ���ʹ��Ԥ�����ļ���Ԥ���ط�ʽ��ȡ���ļ�ֻ��ͨ��Ԥ����API��װ����£���������ͨģʽ���ã�APIͬ��
- Uninstall������ж�ص�ǰ��װ�ļ�������У�
- Launch������������ǰ��װλ�õ���Ϸ

## ����

����Ŀ��Example

## ��л

- [7-zip](https://7-zip.org/) - It is used as a decompression module.
- [bit7z](https://github.com/rikyoz/bit7z) - Provides an API for manipulating 7z.dll.
- [HDiffPatch](https://github.com/sisong/HDiffPatch) - Provide updated game features.
- [AFComponents](https://github.com/acgnfun/AFComponents) - Provides a simple API for creating shortcuts.
