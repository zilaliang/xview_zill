#include "camerarecord.h"
#include"xdemux_task.h"
#include"xmux_task.h"
#include<chrono>
#include<iomanip>
#include<sstream>
#include<ctime>
using namespace std;
using namespace chrono;
static std::string GetFileName(string path) {
	stringstream ss;
	auto t = system_clock::to_time_t(system_clock::now());
	std::tm tm_time;
	localtime_s(&tm_time, &t);

	auto time_str=put_time(&tm_time, "%Y_%m_%d_%H_%M_%S");
	ss << path << "/" << "cam_" << time_str << ".mp4";
	return ss.str();
}
void CameraRecord::Main() {
	XDemuxTask demux;
	XMuxTask mux;
	if (rtsp_url_.empty())
	{
		LOGERROR("open rtsp_url failed");
		return;
	}
	while (!is_exit_)
	{
		if (demux.Open(rtsp_url_))
		{
			break;
		}
		MSleep(10);
		continue;
	}
	auto vpara = demux.CopyVideoPara();
	if (!vpara)
	{
		LOGERROR("demux.CopyVideoPara failed");
		//内部接口应该考虑资源的释放
		demux.Stop();
		return;
	}
	demux.Start();//提前启动防止超时
	auto apara = demux.CopyAudioPara();
	AVCodecParameters* para = nullptr;
	AVRational* time_base = nullptr;

	if (apara)
	{
		para = apara->para;
		time_base = apara->time_base;
	}
	if (!mux.Open(GetFileName(save_path_).c_str(), vpara->para, vpara->time_base, para, time_base))
	{
		LOGERROR("mux.Open rtsp_url_ failed");
		demux.Stop();
		mux.Stop();
		return;
	}
	demux.set_next(&mux);
	mux.Start();

	auto cur = NowMs();
	while (!is_exit_)
	{
		if (NowMs() - cur > file_sec_ * 1000)
		{
			cur = NowMs();
			mux.Stop();
			if (!mux.Open(GetFileName(save_path_).c_str(), vpara->para, vpara->time_base, para, time_base))
			{
				LOGERROR("mux.Open rtsp_url_ failed");
				demux.Stop();
				mux.Stop();
				return;
			}
			mux.Start();
		}
	}
	MSleep(3000);
	mux.Stop();
	demux.Stop();
}