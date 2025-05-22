#include<QStyleOption>
#include<QPainter>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QListWidget>
#include<QDebug>
#include"xdecode_task.h"
#include"xdemux_task.h"
#include"xvideo_view.h"
#include "camera_config.h"
#include "camerawidget.h"
CameraWidget::CameraWidget(QWidget* p):QWidget(p){
	this->setAcceptDrops(true);
}

//��ק����
void CameraWidget::dragEnterEvent(QDragEnterEvent* e) {
	e->acceptProposedAction();
}
//��ק�ɿ�
void CameraWidget::dropEvent(QDropEvent* e) {
	//�õ�url
	auto wid = (QListWidget*)e->source();
	auto cam = CameraConfig::Instance()->GetCam(wid->currentRow());
	Open(cam.url);
}
//��Ⱦ����
void CameraWidget::paintEvent(QPaintEvent* e) {
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
bool CameraWidget::Open(const char* url) {
	if (demux_)
		demux_->Stop();
	if (decode_)
		decode_->Stop();
	//�򿪽��װ
	demux_ = new XDemuxTask();
	if (!demux_->Open(url))
	{
		return false;
	}
	//�򿪽�����
	decode_ = new XDecodeTask();
	auto para = demux_->CopyVideoPara();
	if(!decode_->Open(para->para))
	{
		return false;
	}
	demux_->set_next(decode_);
	view_ = XVideoView::Create();
	view_->set_win_id((void*)winId());
	view_->Init(para->para);
	demux_->Start();
	decode_->Start();
	return true;
}

void CameraWidget::Draw() {
	if (!demux_ || !decode_ || !view_)return;
	auto f = decode_->GetFrame();
	if (!f)return;
	view_->DrawFrame(f);
	XFreeFrame(&f);
}

CameraWidget::~CameraWidget() {
	if (demux_)
	{
		demux_->Stop();
		delete demux_;
		demux_ = nullptr;
	}
	if (decode_)
	{
		decode_->Stop();
		delete decode_;
		decode_ = nullptr;
	}
	if (view_)
	{
		view_->Close();
		delete view_;
		view_ = nullptr;
	}
}