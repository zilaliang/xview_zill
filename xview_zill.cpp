#include "xview_zill.h"
#include<QMouseEvent>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QString>
#include<QContextMenuEvent>
#include<QDebug>
#include<QGridLayout>
#include<QListWidgetItem>
#include<QDialog>
#include<QFormLayout>
#include<QLineEdit>
#include<QMessageBox>
#include"camera_config.h"
#define CAM_CONF_PATH "cams.db"
#define C(s) QString::fromLocal8Bit(s)
static QWidget* cam_wids[16] = { 0 };

XView_Zill::XView_Zill(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    auto vlay = new QVBoxLayout();
    vlay->setContentsMargins(0, 0, 0, 0);
    vlay->setSpacing(0);
    vlay->addWidget(ui.head);
    vlay->addWidget(ui.body);
    this->setLayout(vlay);
    auto hlay = new QHBoxLayout();
    ui.body->setLayout(hlay);
    hlay->setContentsMargins(0, 0, 0, 0);
    hlay->addWidget(ui.left);
    hlay->addWidget(ui.cams);
    this->setLayout(hlay);

    //初始化右键菜单
    auto m = left_menu_.addMenu(C("视图"));
    auto a=m->addAction(C("1窗口"));
    connect(a, SIGNAL(triggered()), this, SLOT(View1()));
    a = m->addAction(C("4窗口"));
    connect(a, SIGNAL(triggered()), this, SLOT(View4()));
    a = m->addAction(C("9窗口"));
    connect(a, SIGNAL(triggered()), this, SLOT(View9()));
    a = m->addAction(C("16窗口"));
    connect(a, SIGNAL(triggered()), this, SLOT(View16()));

    View9();
    CameraConfig::Instance()->Load(CAM_CONF_PATH);
    RefreshCams();
}
static bool mouse_press = false;
static QPoint mouse_point;
//鼠标事件 用于拖动窗口
void XView_Zill::mouseMoveEvent(QMouseEvent* ev)
{
    if (!mouse_press)
    {
        QWidget::mouseMoveEvent(ev);
        return;
    }
    this->move(ev->globalPos() - mouse_point);
}
void XView_Zill::XView_Zill::mousePressEvent(QMouseEvent* ev) {
    if (ev->button() == Qt::LeftButton)
    {
        mouse_press = true;
        mouse_point = ev->pos();
    }
}
void XView_Zill::mouseReleaseEvent(QMouseEvent* ev) {
    mouse_press = false;
}

void XView_Zill::resizeEvent(QResizeEvent* ev) {
    int x = width() - ui.head_button->width();
    int y = ui.head_button->y();
    ui.head_button -> move(x, y);

    ui.status->move(x/2, y);
}
void XView_Zill::contextMenuEvent(QContextMenuEvent* event) {
    left_menu_.exec(QCursor::pos());
    event->accept();
}
void XView_Zill::View(int count) {
    qDebug()<<"View"<<count;
    //2X2 3X3 4X4
    int cols = sqrt(count);
    //总窗口数量
    int wid_size = sizeof(cam_wids) / sizeof(QWidget*);
    //初始化布局器
    auto lay = (QGridLayout*)ui.cams->layout();
    if (!lay)
    {
        lay = new QGridLayout();
        lay->setContentsMargins(2, 2, 2, 2);
        lay->setSpacing(2);
        ui.cams->setLayout(lay);
    }
    //初始化窗口
    for (int i = 0; i < count; i++)
    {
        if (!cam_wids[i])
        {
            cam_wids[i] = new QWidget();
            cam_wids[i]->setStyleSheet("background-color:rgb(51,51,51);");
        }
        lay->addWidget(cam_wids[i], i / cols, i % cols);
    }


    for (int i = count; i < wid_size; i++)
    {
        if (cam_wids[i])
        {
            delete cam_wids[i];
            cam_wids[i] = nullptr;
        }
    }
}


void XView_Zill::RefreshCams() {
    auto c = CameraConfig::Instance();
    ui.cam_list->clear();
    int count = c->GetCamCount();
    for (int i = 0; i < count; i++)
    {
        auto cam = c->GetCam(i);
        auto item = new QListWidgetItem(QIcon(":/XView_Zill/img/camera_list.png"),
            C(cam.name));
        ui.cam_list->addItem(item);
    }
}

XView_Zill::~XView_Zill()
{
}

void XView_Zill::MaxWindow()
{
    ui.max->setVisible(false);
    ui.normal->setVisible(true);
    showMaximized();
}
void XView_Zill::NormalWindow()
{
    ui.max->setVisible(true);
    ui.normal->setVisible(false);
    showNormal();
}
void XView_Zill::View1() {
    View(1);
}
void XView_Zill::View4() {
    View(4);
}
void XView_Zill::View9() {
    View(9);
}
void XView_Zill::View16() {
    View(16);
}
//新增摄像机
void XView_Zill::AddCam() {
    qDebug() << "hover";
    QDialog dlg(this);
    dlg.resize(600, 200);
    QFormLayout lay;
    dlg.setLayout(&lay);
    QLineEdit name_edit;
    lay.addRow(C("名称"),&name_edit);

    QLineEdit url_edit;
    lay.addRow(C("主码流"), &url_edit);

    QLineEdit sub_url_edit;
    lay.addRow(C("辅码流"), &sub_url_edit);

    QLineEdit save_path_edit;
    lay.addRow(C("保存目录"), &save_path_edit);

    QPushButton save;
    save.setText(C("保存"));
    connect(&save, SIGNAL(clicked()), &dlg, SLOT(accept()));
    lay.addRow("", &save);
    for (;;)
    {
        if (dlg.exec() == QDialog::Accepted)
        {
            if (name_edit.text().isEmpty())
            {
                QMessageBox::information(0, "erro", C("请输入名称"));
                continue;
            }
            if (url_edit.text().isEmpty())
            {
                QMessageBox::information(0, "erro", C("请输入主码流"));
                continue;
            }
            if (sub_url_edit.text().isEmpty())
            {
                QMessageBox::information(0, "erro", C("请输入辅码流"));
                continue;
            }
            if (save_path_edit.text().isEmpty())
            {
                QMessageBox::information(0, "erro", C("请输入保存路径"));
                continue;
            }
            break;
        }
        return;
    }
    CameraData data;
    strcpy_s(data.name, name_edit.text().toLocal8Bit());
    strcpy_s(data.url, url_edit.text().toLocal8Bit());
    strcpy_s(data.url_sub, sub_url_edit.text().toLocal8Bit());
    strcpy_s(data.save_path, save_path_edit.text().toLocal8Bit());
    CameraConfig::Instance()->Push(data);//插入数据
    CameraConfig::Instance()->Save(CAM_CONF_PATH);//保存到文件
    RefreshCams();//刷新显示
}