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
     //��ק����
    void dragEnterEvent(QDragEnterEvent* e)override;
    //��ק�ɿ�
    void dropEvent(QDropEvent* e)override;

    //��Ⱦ����
    void paintEvent(QPaintEvent* e)override;

    //�򿪶�Ӧ��rtsp��
    bool Open(const char* url);

    //��Ⱦ����
    void Draw();

    //����
    ~CameraWidget();
private:
    XDecodeTask* decode_=nullptr;
    XDemuxTask* demux_=nullptr;
    XVideoView* view_=nullptr;
};

