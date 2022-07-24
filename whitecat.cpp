#include "whitecat.h"
#include<QDesktopWidget>
#include<QApplication>
#include<QPushButton>
#include<QTime>         //使用了QTime函数
#include <QtGlobal>    //qsrand和qrand这两个函数在这里面

int whiteCat::flag_Click = 1;
int whiteCat::flag_Realse = 1;
int whiteCat::flag_1 = 1;
int whiteCat::flag_2 = 1;
int whiteCat::flag_ChangePic = 2;

whiteCat::whiteCat(QWidget *parent) : QWidget(parent)
{

    //初始化 单击双击判断条件
    m_clickedTimer = new QTimer(this);

    connect(m_clickedTimer,&QTimer::timeout,this,&whiteCat::slotClicked);


    this->m_WhiteCat_Pix.load(":/new/prefix2/whitecat/shime1.png");

    //设置猫的尺寸
    this->setFixedSize(this->m_WhiteCat_Pix.width(),this->m_WhiteCat_Pix.height());

    //创建菜单
    this->m_Menu = new QMenu(this);

    QAction *Exit = new QAction("退出",this);
    QAction *Sit = new QAction("坐下",this);
    QAction *Walk = new QAction("动起来",this);

    m_Menu->addAction(Walk);
    m_Menu->addSeparator();
    m_Menu->addAction(Sit);
    m_Menu->addSeparator();
    m_Menu->addAction(Exit);

    connect(Exit,&QAction::triggered,[=](){
        exit(0);
    });

    connect(Sit,&QAction::triggered,[=](){
        this->CatSit_min = 16;
        emit m_Sit();
    });

    connect(Walk,&QAction::triggered,[=](){
        emit m_Walk();
    });

    //创建定时器对象
    this->timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X = ((QWidget*)this->parent())->frameGeometry().topLeft().x();
        win_Y = ((QWidget*)this->parent())->frameGeometry().topLeft().y();

        QString str2 = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatWalk2_min++);

        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatWalk_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        QImage image2(str2);
        QImage mirroredImage2 = image2.mirrored(true, false);

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            if(win_Y>-this->height() && win_Y<100)
            {
                this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage2);
            }
            else
            {
                this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
            }
        }
        if(flag_ChangePic == 2)//原图
        {
            if(win_Y>-this->height() && win_Y<100)
            {
                this->m_WhiteCat_Pix.load(str2);
            }else
            {
                this->m_WhiteCat_Pix.load(str);
            }
        }


        if(this->CatWalk_min > this->CatWalk_max)
        {
            this->CatWalk_min = 1;
        }
        if(this->CatWalk2_min > this->CatWalk2_max)
        {
            this->CatWalk2_min = 34;
        }

        //掏出自定义 切图 信号
        emit changePix();
    });

    this->timer_Catch = new QTimer(this);
    connect(timer_Catch,&QTimer::timeout,[=](){

        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatCatch_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值

        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();
        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }

        if(this->CatCatch_min > this->catCatch_max)
        {
            this->CatCatch_min = 5;
        }

        emit changePix_Catch();
    });

    this->timer_Dclick = new QTimer(this);
    connect(timer_Dclick,&QTimer::timeout,[=](){
        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatChange_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }
        if(this->CatChange_min > this->CatChange_max)
        {
            this->CatChange_min = 38;
            flag_Click = 2;
        }
        emit changePix_Dclick();
    });

    this->timer_Realse = new QTimer(this);
    connect(timer_Realse,&QTimer::timeout,[=](){
        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatRealse_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }
        if(this->CatRealse_min > this->CatRealse_max)
        {
            this->CatRealse_min = 47;
            flag_Realse = 2;
        }

        emit changePix_Realse();
    });

    this->timer_Climb = new QTimer(this);
    connect(timer_Climb,&QTimer::timeout,[=](){
        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatClimb_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }
        if(this->CatClimb_min > this->CatClimb_max)
        {
            this->CatClimb_min = 12;
        }
        emit changePix_Climb();
    });

    this->timer_Strike = new QTimer(this);
    connect(timer_Strike,&QTimer::timeout,[=](){
        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatStrike_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }
        if(this->CatStrike_min > this->CatStrike_max)
        {
            this->CatStrike_min = 60;
            flag_1 = 2;
        }
        emit changePix_Strike();
    });

    this->timer_Sit = new QTimer(this);
    connect(timer_Sit,&QTimer::timeout,[=](){
        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatSit_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }
        if(this->CatSit_min > this->CatSit_max)
        {
            this->CatSit_min = 18;

        }

        emit changePix_Sit();
    });

    this->timer_Ball = new QTimer(this);
    connect(timer_Ball,&QTimer::timeout,[=](){
        QString str = QString(":/new/prefix2/whitecat/shime%1.png").arg(this->CatBall_min++);

        QImage image(str);
        QImage mirroredImage = image.mirrored(true, false);

        //获取屏幕
        QDesktopWidget * desk = QApplication::desktop();
        //当前位置左上角坐标的X值
        win_X =((QWidget*)this->parent())->frameGeometry().topLeft().x();

        if(win_X <= 0.9*(-this->width()))
        {
            flag_ChangePic = 1;
        }
        if(win_X >= 0.99*(desk->width()))
        {
            flag_ChangePic = 2;
        }
        if(flag_ChangePic == 1)//反向
        {
            this->m_WhiteCat_Pix = QPixmap::fromImage(mirroredImage);
        }
        if(flag_ChangePic == 2)//原图
        {
            this->m_WhiteCat_Pix.load(str);
        }
        if(this->CatBall_min > this->CatBall_max)
        {
            this->CatBall_min = 22;
            flag_2 = 2;
        }

        emit changePix_Ball();
    });
}

void whiteCat::slotClicked()
{
    if (clickCount == 1) {//只点击了一次

        //qDebug()<<"单击";
    }
    else if (clickCount == 2) {//双击鼠标
        //qDebug()<<"双击";
        emit this->mouse_Dclick();//双击信号
    }
        clickCount = 0;

    m_clickedTimer->stop();
}

void whiteCat::running()
{
    this->timer->start(130);
}
void whiteCat::running_Catch()
{
    this->timer_Catch->start(150);
}
void whiteCat::running_Dclick()
{
    this->timer_Dclick->start(200);
}
void whiteCat::running_Realse()
{
    this->timer_Realse->start(130);
}
void whiteCat::running_Climb()
{
    this->timer_Climb->start(130);
}
void whiteCat::running_Strike()
{
    this->timer_Strike->start(180);
}
void whiteCat::running_Sit()
{
    this->timer_Sit->start(180);
}
void whiteCat::running_Ball()
{
    this->timer_Ball->start(170);
}

void whiteCat::mousePressEvent(QMouseEvent *event)
{


    //鼠标按下的时候 记录分量
    //((QWidget*)this->parent())->frameGeometry().topLeft() 获取当前窗口左上角的坐标
    this->m_pos = event->globalPos() - ((QWidget*)this->parent())->frameGeometry().topLeft();

    //鼠标按下状态为真
    this->mouseDown = true;

    //如果按下鼠标左键，给出信号
//    if(event->button() == Qt::LeftButton )
//    {
//        qDebug()<<"单击";
//        emit this->mouse_PressLeft();
//    }

    if (event->button() & Qt::LeftButton) {
        emit this->mouse_PressLeft();
            if (!m_clickedTimer->isActive()) {
                m_clickedTimer->start(500);
                clickCount++;
            } else {
                clickCount++;
            }
        }

    //如果是鼠标右键，弹出菜单
    if(event->button() == Qt::RightButton)
    {
        emit this->mouse_PressRight();

        //弹出菜单 弹的位置和鼠标当前位置一致
        this->m_Menu->popup(QCursor::pos());

    }

    //如果菜单 通过别的方式消失，猫继续走
    connect(this->m_Menu,&QMenu::aboutToHide,[=](){
        this->mouseDown = false;

    });
}

void whiteCat::mouseMoveEvent(QMouseEvent *event)
{
    //在移动过程中 反向获取窗口最终移动位置在哪
    emit this->moving(event->globalPos() - this->m_pos);
}

void whiteCat::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标按下状态为假
    this->mouseDown = false;

    //添加鼠标释放信号
    emit this->mouse_Realse();
}

