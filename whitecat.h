#ifndef WHITECAT_H
#define WHITECAT_H

#include <QWidget>
#include<QString>
#include<QPixmap>
#include<QMenu>
#include<QTimer>
#include<QPoint>
#include<QMouseEvent>
#include<QtDebug>
class whiteCat : public QWidget
{
    Q_OBJECT
public:
    explicit whiteCat(QWidget *parent = nullptr);

    //猫显示图片
    QPixmap m_WhiteCat_Pix;


    //切换图片标志位 2原图 1反向
    static int flag_ChangePic;

    //双击标志
    static int flag_Click;
    //释放标志
    static int flag_Realse;
    //按钮1标志
    static int flag_1;
    //按钮2标志
    static int flag_2;

    int clickCount = 0;//用来区分是否双击

    int CatWalk_min = 1;
    int CatWalk_max = 3;

    int CatWalk2_min = 34;
    int CatWalk2_max = 36;

    int CatCatch_min = 5;
    int catCatch_max = 9;

    int CatChange_min = 38;
    int CatChange_max = 46;

    int CatRealse_min = 47;
    int CatRealse_max = 50;

    int CatClimb_min = 12;
    int CatClimb_max = 14;

    int CatStrike_min = 60;
    int CatStrike_max = 67;

    int CatSit_min = 16;
    int CatSit_max = 25;

    int CatBall_min = 24;
    int CatBall_max = 33;

    //当前位置左上角坐标的X值
    int win_X;
    //当前位置左上角坐标的Y值
    int win_Y;

    //定时器
    QTimer * timer;
    QTimer * timer_Catch;
    QTimer * timer_Dclick;
    QTimer * timer_Realse;
    QTimer * timer_Climb;
    QTimer * timer_Strike;
    QTimer * timer_Sit;
    QTimer * timer_Ball;

    QTimer*  m_clickedTimer;//点击时间，用来区分单击和双击

    void slotClicked();     //槽函数

    //执行动画函数
    void running();
    void running_Catch();
    void running_Dclick();
    void running_Realse();
    void running_Climb();
    void running_Strike();
    void running_Sit();
    void running_Ball();

    //记录分量坐标
    QPoint m_pos;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标双击事件
    //void mouseDoubleClickEvent(QMouseEvent *event);

    //鼠标按下状态
    bool mouseDown = false;

    //右键菜单，帮助实现退出
    QMenu * m_Menu;

signals:
    //自定义信号 切图信号
    void changePix();
    void changePix_Catch();
    void changePix_Dclick();
    void changePix_Realse();
    void changePix_Climb();
    void changePix_Strike();
    void changePix_Sit();
    void changePix_Ball();

    //自定义信号 拖拽后主场景应该移动的位置
    void moving(QPoint point);

    //按下鼠标左键的信号
    void mouse_PressLeft();

    //按下鼠标右键的信号
    void mouse_PressRight();

    //鼠标双击信号
    void mouse_Dclick();

    //鼠标释放信号
    void mouse_Realse();

    //点击坐下按钮信号
    void m_Sit();

    //点击动起来按钮信号
    void m_Walk();

};

#endif // WHITECAT_H
