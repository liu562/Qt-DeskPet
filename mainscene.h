#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<whitecat.h>
#include<QPainter>
#include<QImage>
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //猫对象指针
    whiteCat * m_Cat;
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //自动移动位置
    QPoint  m_Auto_Pos;

    //自动移动的定时器
    QTimer * timer_AUtoMOv;
    //向上移动的定时器
    QTimer * timer_MovUp;

    //x轴判断标志
    int flag_x = 1;

    //y轴判断标志
    int flag_y = 2;

signals:

    //信号动起来返回
    void back();

};

#endif // WIDGET_H
