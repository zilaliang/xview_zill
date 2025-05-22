#pragma once

#include <QtWidgets/QWidget>
#include "ui_xview_zill.h"
#include<QMenu>
class XView_Zill : public QWidget
{
    Q_OBJECT

public:
    XView_Zill(QWidget *parent = nullptr);

    //鼠标事件 用于拖动窗口
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    //窗口大小发生变化
    void resizeEvent(QResizeEvent* ev)override;
    //右键打开鼠标
    void contextMenuEvent(QContextMenuEvent* event)override;
    //显示窗口
    void View(int count);
    //刷新左侧相机列表
    void RefreshCams();
    void SetCam(int index);

    ~XView_Zill();

public slots:
    void MaxWindow();
    void NormalWindow();
    //显示不同数量的窗口
    void View1();
    void View4();
    void View9();
    void View16();
    void AddCam();
    void SetCam();
    void DelCam();


private:
    Ui::XView_ZillClass ui;
    QMenu left_menu_;
};
