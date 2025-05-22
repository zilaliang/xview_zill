#include "camera_config.h"
#include <fstream>
using namespace std;
void CameraConfig::Push(const CameraData& data) {
	unique_lock<mutex>lock(mux_);
	cams_.push_back(data);
}

bool CameraConfig::SetCam(int index, const CameraData& data) {
	unique_lock<mutex>lock(mux_);
	if (index<0 || index>cams_.size())
		return false;
	cams_[index] = data;
	return true;
}
bool CameraConfig::DelCam(int index) {
	unique_lock<mutex>lock(mux_);
	if (index<0 || index>cams_.size())
		return false;
	cams_.erase(cams_.begin() + index);
	return true;
}

CameraData CameraConfig::GetCam(int index) {
	unique_lock<mutex>lock(mux_);
	if (index<0 || index>cams_.size())
		return CameraData();
	return cams_[index];
}
int CameraConfig::GetCamCount() {
	unique_lock<mutex>lock(mux_);
	return cams_.size();
}

bool CameraConfig::Save(const char* path) {
	if (!path)return false;

	ofstream ofs(path, ios::binary);
	if (!ofs)return false;
	unique_lock<mutex>lock(mux_);
	for (auto cam : cams_)
	{
		ofs.write((char*)&cam, sizeof(cam));
	}
	ofs.close();
	return true;
}

bool CameraConfig::Load(const char* path) {
	if (!path)return false;
	ifstream ifs(path, ios::binary);
	if (!ifs)return false;
	CameraData data;
	unique_lock<mutex>lock(mux_);
	cams_.clear();
	for (;;)
	{
		ifs.read((char*)&data, sizeof(data));
		//读到的文件大小是否为预期的大小 ， 如果不一样就说明读到了文件末尾
		if(ifs.gcount()!=sizeof(data))
		{
			ifs.close();
			return true;
		}
		cams_.push_back(data);
	}
	ifs.close();
	return true;
}
