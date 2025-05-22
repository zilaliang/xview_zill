#pragma once
#include <QWidget>
class XDecodeTask;
class XDemuxTask;
class XVideoView;
class CameraWidget :
    public QWidget
{
    Q_OBJECT
public:
    CameraWidget(QWidget* p=nullptr);
     //拖拽进入
    void dragEnterEvent(QDragEnterEvent* e)override;
    //拖拽松开
    void dropEvent(QDropEvent* e)override;

    //渲染部分
    void paintEvent(QPaintEvent* e)override;

    //打开对应的rtsp流
    bool Open(const char* url);

    //渲染部分
    void Draw();

    //析构
    ~CameraWidget();
private:
    XDecodeTask* decode_=nullptr;
    XDemuxTask* demux_=nullptr;
    XVideoView* view_=nullptr;
};

