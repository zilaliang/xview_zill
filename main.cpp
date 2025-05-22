#include "xview_zill.h"
#include <QtWidgets/QApplication>
#include"camera_config.h"
#include<iostream>
#define CAM_CONF_PATH "cams.db"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XView_Zill w;
    w.show();

    auto cg = CameraConfig::Instance();

    //¶ÁÈ¡
    cg->Load(CAM_CONF_PATH);
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


    return a.exec();
}
