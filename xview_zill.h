#pragma once

#include <QtWidgets/QWidget>
#include "ui_xview_zill.h"
#include<QMenu>
class XView_Zill : public QWidget
{
    Q_OBJECT

public:
    XView_Zill(QWidget *parent = nullptr);

    //����¼� �����϶�����
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    //���ڴ�С�����仯
    void resizeEvent(QResizeEvent* ev)override;
    //�Ҽ������
    void contextMenuEvent(QContextMenuEvent* event)override;
    //��ʾ����
    void View(int count);
    //ˢ���������б�
    void RefreshCams();
    void SetCam(int index);

    ~XView_Zill();

public slots:
    void MaxWindow();
    void NormalWindow();
    //��ʾ��ͬ�����Ĵ���
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
