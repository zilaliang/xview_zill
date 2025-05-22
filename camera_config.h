#pragma once
#include<vector>
#include<mutex>
struct CameraData
{
	char name[1024] = { 0 };
	char url[4096] = { 0 };
	char url_sub[4096] = { 0 };
	char save_path[4096] = { 0 };
};
class CameraConfig
{
public:
	//Ψһ���� ����ģʽ ����������ȫ�ֵ�
	static CameraConfig* Instance()
	{
		static CameraConfig re;
		return &re;
	}
	//���������
	void Push(const CameraData& data);
	//�޸������
	bool SetCam(int index, const CameraData& data);
	//ɾ�������
	bool DelCam(int index);
	//��ȡ����ͷ
	CameraData GetCam(int index);

	//��ȡ�����������
	int GetCamCount();

	//�洢�ļ�
	bool Save(const char* path);
	//��ȡ�ļ�
	bool Load(const char* path);
private:
	CameraConfig() {};
	std::vector<CameraData>cams_;
	std::mutex mux_;
};

