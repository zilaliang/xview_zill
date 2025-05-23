
#include <QtWidgets/QApplication>
#include<iostream>
#include<QDir>
#include "xview_zill.h"
#include"camera_config.h"
#include"camerarecord.h"
#define CAM_CONF_PATH "cams.db"
int main(int argc, char *argv[])
{
    const char* save_path = "./video/0/";
    QDir dir;
    dir.mkpath(save_path);

    CameraRecord xr;
    xr.set_rtsp_url("rtsp://127.0.0.1:8554/1");
    xr.set_save_path(save_path);
    xr.Start();

    QApplication a(argc, argv);
    XView_Zill w;
    w.show();

    //auto cg = CameraConfig::Instance();

    ////¶ÁÈ¡
    //cg->Load(CAM_CONF_PATH);
    //for (int i = 0; i < cg->GetCamCount(); i++) {
    //    auto cam = cg->GetCam(i);
    //    std::cout << cam.name << std::endl;
    //}
   
    //std::cout << "=============" << std::endl;

    //{
    //    CameraData dt;
    //    strcpy_s(dt.name, "camera1");
    //    strcpy_s(dt.url, "camera1");
    //    strcpy_s(dt.url_sub, "camera1");
    //    strcpy_s(dt.save_path, "camera1");
    //    cg->Push(dt);
    //}
    //{
    //    CameraData dt;
    //    strcpy_s(dt.name, "camera1");
    //    strcpy_s(dt.url, "camera1");
    //    strcpy_s(dt.url_sub, "camera1");
    //    strcpy_s(dt.save_path, "camera1");
    //    cg->Push(dt);
    //}
    //for (int i = 0; i < cg->GetCamCount(); i++) {
    //    auto cam=cg->GetCam(i);
    //    std::cout << cam.name << std::endl;
    //}



    //std::cout << "=============" << std::endl;
    //auto d1 = cg->GetCam(0);
    //strcpy_s(d1.name, "jjjj");
    //cg->SetCam(0,d1);
    //for (int i = 0; i < cg->GetCamCount(); i++) {
    //    auto cam = cg->GetCam(i);
    //    std::cout << cam.name << std::endl;
    //}

    //std::cout << "=============" << std::endl;
    //for (int i = 0; i < cg->GetCamCount(); i++) {
    //    cg->DelCam(i);
    //}
    //cg->Save(CAM_CONF_PATH);
    //for (int i = 0; i < cg->GetCamCount(); i++) {
    //    auto cam = cg->GetCam(i);
    //    std::cout << cam.name << std::endl;
    //    
    //}


    auto re= a.exec();
    xr.Stop();
    return re;
}
