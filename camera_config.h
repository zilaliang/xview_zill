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
	//唯一对象 单例模式 生存周期是全局的
	static CameraConfig* Instance()
	{
		static CameraConfig re;
		return &re;
	}
	//插入摄像机
	void Push(const CameraData& data);
	//修改摄像机
	bool SetCam(int index, const CameraData& data);
	//删除摄像机
	bool DelCam(int index);
	//获取摄像头
	CameraData GetCam(int index);

	//获取相机返回数量
	int GetCamCount();

	//存储文件
	bool Save(const char* path);
	//读取文件
	bool Load(const char* path);
private:
	CameraConfig() {};
	std::vector<CameraData>cams_;
	std::mutex mux_;
};

