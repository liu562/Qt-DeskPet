#include "mainscene.h"
#include<QIcon>
#include<QDesktopWidget>
#include<QApplication>
#include<QDebug>
#include<QPoint>
#include<QPushButton>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{


    //设置图标
    QImage image(":/new/prefix2/whitecat/shime1.png");
    QImage mirrowedImage = image.mirrored(false,true);
    QPixmap pixmap = QPixmap::fromImage(mirrowedImage);
    this->setWindowIcon(QIcon(pixmap));

    //创建猫对象
    this->m_Cat = new whiteCat;

    //将猫对象显示在窗口中
    this->m_Cat->setParent(this);

    //设置窗口大小
    this->setFixedSize(this->m_Cat->width(),this->m_Cat->height());

    QPushButton *Btn1 = new QPushButton;
    Btn1->setParent(this);
    Btn1->resize(50,50);//设置按钮大小
    //正向
    Btn1->move(5,15);
    //反向
    //Btn1->move(70,15);

    //设置按钮透明
    Btn1->setFlat(true);
    Btn1->setStyleSheet("background-color: rgba(0,0,0,0)");

    //创建扔球按钮事件
    QPushButton *Btn2 = new QPushButton;
    Btn2->setParent(this);
    Btn2->resize(20,20);//设置按钮大小
    Btn2->setText("T");
    //Btn2->setStyleSheet("background-color: rgba(0,255,0,80)");
    Btn2->setStyleSheet("background-color: rgba(0,255,0,100);border-radius:10px;padding:2px 4px;");//圆形
    //正向
    Btn2->move(100,15);
    //反向
    //Btn2->move(0,15);


    //获取屏幕
    QDesktopWidget * desk = QApplication::desktop();

    //启动定时器
    this->m_Cat->running();
    //this->m_Cat->running_Catch();



    //监听猫切图信号
    connect(this->m_Cat,&whiteCat::changePix,[=](){
        Btn2->hide();
        if(whiteCat::flag_ChangePic == 1)
        {
            Btn1->move(70,15);
            Btn2->move(0,15);
        }
        else
        {
            Btn1->move(5,15);
            Btn2->move(100,15);
        }

        if(this->frameGeometry().x()<desk->width()*0.5 || this->frameGeometry().y()<desk->height()*0.5)
        {
            Btn1->lower();
            Btn1->setEnabled(false);
        }
        else
        {
            Btn1->raise();
            Btn1->setEnabled(true);
        }

        if(this->frameGeometry().x()>250 || this->frameGeometry().y()>400 ||this->frameGeometry().y()<100 || this->frameGeometry().x()<230)
        {
            this->timer_MovUp->stop();
            update();
        }
        else
        {
            this->m_Cat->timer->stop();
            //暂停图框移动
            this->timer_AUtoMOv->stop();

            this->m_Cat->running_Climb();
        }

        connect(Btn1,&QPushButton::clicked,[=](){
            whiteCat::flag_1 =1;
            if(whiteCat::flag_1 == 1)
            {
                this->m_Cat->timer->stop();
                //暂停图框移动
                this->timer_AUtoMOv->stop();
                this->m_Cat->timer_Sit->stop();
                this->m_Cat->running_Strike();
                connect(this->m_Cat,&whiteCat::changePix_Strike,[=](){
                    update();
                    if(whiteCat::flag_1 == 2)
                    {
                        this->m_Cat->timer_Strike->stop();
                        this->m_Cat->running();
                        this->timer_AUtoMOv->start();
                    }

                });
            }
        });

    });


    //创建定时器对象
    this->timer_MovUp = new QTimer(this);
    this->timer_MovUp->start(50);
    connect(timer_MovUp,&QTimer::timeout,[=](){
        //如果鼠标没有按下，才向前自动移动
        if(this->m_Cat->mouseDown != true)
        {
        this->m_Auto_Pos.setX(this->m_Auto_Pos.x());
        this->m_Auto_Pos.setY(this->m_Auto_Pos.y()-6);
        }
        //窗口同步移动
        this->move(this->m_Auto_Pos);

    });
    connect(this->m_Cat,&whiteCat::changePix_Climb,[=](){
        this->timer_AUtoMOv->stop();
        this->timer_MovUp->start();

        update();
        if(this->frameGeometry().y()<100 ||this->frameGeometry().x()<230)
        {
            this->m_Cat->timer_Climb->stop();
            this->timer_AUtoMOv->start();
            this->timer_MovUp->stop();
            this->m_Cat->timer->start();
        }
    });


//    connect(this->m_Cat,&whiteCat::changePix_Catch,[=](){
//        update();
//    });

    //监听猫拖拽移动的信号
    connect(this->m_Cat,&whiteCat::moving,[=](QPoint point){
        this->move(point);
        this->timer_MovUp->stop();
        this->m_Cat->timer_Climb->stop();
        this->m_Cat->timer_Sit->stop();
        this->m_Cat->timer_Strike->stop();
        this->m_Cat->timer_Dclick->stop();
        this->m_Cat->timer_Ball->stop();
        m_Auto_Pos = point;//鼠标拖拽的时候更新当前窗口的位置

    });

    //按下鼠标左键，猫被提留
    connect(this->m_Cat,&whiteCat::mouse_PressLeft,[=](){
        Btn1->raise();
        Btn2->hide();
        if(this->m_Cat->mouseDown == true)
        {
            this->m_Cat->timer->stop();
            this->timer_MovUp->stop();
            this->m_Cat->timer_Sit->stop();
            this->m_Cat->timer_Climb->stop();
            this->m_Cat->timer_Strike->stop();
            this->m_Cat->timer_Dclick->stop();
            this->m_Cat->timer_Ball->stop();
            //启动定时器
            this->m_Cat->running_Catch();
            //监听猫切图信号
            connect(this->m_Cat,&whiteCat::changePix_Catch,[=](){
                update();
                if(this->m_Cat->mouseDown == false)
                {
                    this->m_Cat->timer_Catch->stop();
                    //this->m_Cat->running();
                }
            });
        }
        connect(this->m_Cat,&whiteCat::mouse_Realse,[=](){
            //qDebug()<<"cdsfvf";
            whiteCat::flag_Realse =1;
            if( whiteCat::flag_Realse == 1)
            {
                this->timer_AUtoMOv->stop();
                this->timer_MovUp->stop();
                this->m_Cat->timer_Climb->stop();
                this->m_Cat->timer_Strike->stop();
                //暂停猫行走定时器
                //this->m_Cat->timer->stop();
                //启动
                this->m_Cat->running_Realse();
                //监听猫切图信号
                connect(this->m_Cat,&whiteCat::changePix_Realse,[=](){
                    update();
                    if(whiteCat::flag_Realse == 2)
                    {
                        this->m_Cat->timer_Realse->stop();
                        this->m_Cat->running();
                        this->timer_AUtoMOv->start();
                    }
                });
            }
        });

    });


    //双击，猫黑化
    connect(this->m_Cat,&whiteCat::mouse_Dclick,[=](){
        Btn1->raise();
        Btn2->hide();
        this->m_Cat->timer_Realse->stop();
        this->timer_MovUp->stop();
        this->m_Cat->timer_Climb->stop();
        this->m_Cat->timer_Strike->stop();
        this->m_Cat->timer_Sit->stop();
        this->m_Cat->timer_Ball->stop();
        //双击标志
        whiteCat::flag_Click =1;
        if( whiteCat::flag_Click == 1)
        {
            //暂停图框移动
            this->timer_AUtoMOv->stop();

            this->m_Cat->timer_Catch->stop();
            //暂停猫行走定时器
            this->m_Cat->timer->stop();
            //启动
            this->m_Cat->running_Dclick();
            //监听猫切图信号
            connect(this->m_Cat,&whiteCat::changePix_Dclick,[=](){
                update();
                if(whiteCat::flag_Click == 2)
                {
                    this->m_Cat->timer_Dclick->stop();
                    this->m_Cat->running();
                    this->timer_AUtoMOv->start();
                }
            });
        }

    });


    //右键坐下
    connect(this->m_Cat,&whiteCat::m_Sit,[=](){
       // 坐下无法触发冲刺生火
        Btn1->setEnabled(false);
        Btn1->lower();

        Btn2->show();
        this->m_Cat->timer->stop();
        this->timer_MovUp->stop();
        this->timer_AUtoMOv->stop();
        this->m_Cat->timer_Climb->stop();
        this->m_Cat->timer_Strike->stop();
        this->m_Cat->timer_Catch->stop();
        this->m_Cat->timer_Dclick->stop();
        this->m_Cat->running_Sit();

        connect(this->m_Cat,&whiteCat::changePix_Sit,[=](){
            update();
        });
        connect(Btn2,&QPushButton::clicked,[=](){
            Btn2->hide();
            whiteCat::flag_2 = 1;
            this->m_Cat->timer_Sit->stop();
            this->m_Cat->running_Ball();
            if(whiteCat::flag_2 == 1)
            {
                connect(this->m_Cat,&whiteCat::changePix_Ball,[=](){
                    update();
                    if(whiteCat::flag_2 == 2)
                    {
                        whiteCat::flag_2 = 1;
                        this->m_Cat->timer_Ball->stop();
                        //this->m_Cat->running();
                        //this->timer_AUtoMOv->start();
                        this->m_Cat->running_Sit();
                        Btn2->show();
                    }
                });
            }

        });
    });

    //右键动起来
    connect(this->m_Cat,&whiteCat::m_Walk,[=](){
        Btn1->raise();
        Btn2->hide();
        //启动定时器
        this->m_Cat->running();
        this->timer_AUtoMOv->start();
        this->m_Cat->timer_Climb->stop();
        this->m_Cat->timer_Strike->stop();
        this->m_Cat->timer_Catch->stop();
        this->m_Cat->timer_Sit->stop();
        //监听猫切图信号
        connect(this->m_Cat,&whiteCat::changePix,[=](){
            if(whiteCat::flag_ChangePic == 1)
            {
                Btn1->move(70,15);
            }
            else
            {
                Btn1->move(5,15);
            }

            if(this->frameGeometry().x()<desk->width()*0.5 || this->frameGeometry().y()<desk->height()*0.5)
            {
                Btn1->lower();
                Btn1->setEnabled(false);
            }
            else
            {
                Btn1->raise();
                Btn1->setEnabled(true);
            }

            if(this->frameGeometry().x()>250 || this->frameGeometry().y()>400 ||this->frameGeometry().y()<100 || this->frameGeometry().x()<230)
            {
                this->timer_MovUp->stop();
                update();
            }
            else
            {
                this->m_Cat->timer->stop();
                //暂停图框移动
                this->timer_AUtoMOv->stop();

                this->m_Cat->running_Climb();
            }

            connect(Btn1,&QPushButton::clicked,[=](){

                whiteCat::flag_1 =1;
                if(whiteCat::flag_1 == 1)
                {
                    this->m_Cat->timer->stop();
                    //暂停图框移动
                    this->timer_AUtoMOv->stop();
                    this->m_Cat->timer_Sit->stop();
                    this->m_Cat->running_Strike();
                    connect(this->m_Cat,&whiteCat::changePix_Strike,[=](){
                        update();
                        if(whiteCat::flag_1 == 2)
                        {
                            this->m_Cat->timer_Strike->stop();
                            this->m_Cat->running();
                            this->timer_AUtoMOv->start();
                        }

                    });
                }
            });

        });
    });


    //创建定时器对象
    this->timer_AUtoMOv = new QTimer(this);

    //启动定时器
    this->timer_AUtoMOv->start(30);

//    //获取屏幕
//    QDesktopWidget * desk = QApplication::desktop();

    //监听定时器
    connect(timer_AUtoMOv,&QTimer::timeout,[=](){

        //如果鼠标没有按下，才向前自动移动
        if(this->m_Cat->mouseDown != true)
        {
            //当猫x轴位于左边时，值为2
            if(this->m_Auto_Pos.x() <= -this->width())
            {
                flag_x = 2;
            }
            //当猫x轴位于右边时，值为1
            if(this->m_Auto_Pos.x() >= desk->width())
            {
                flag_x = 1;
            }
            if(flag_x == 1)//猫位于右边向左移动
            {
                this->m_Auto_Pos.setX(this->m_Auto_Pos.x()-5);
                this->m_Auto_Pos.setY(this->m_Auto_Pos.y()-2);

                if(this->m_Auto_Pos.y() <= -this->height())
                {
                    flag_y = 2;//当猫y轴位于上面时，值为2
                }
                if(this->m_Auto_Pos.y() >= desk->height())
                {
                    flag_y = 1;//当猫y轴位于下面时，值为1
                }
                if(flag_y == 1)//当猫触到屏幕下面边框时向上移动
                {
                    this->m_Auto_Pos.setY(this->m_Auto_Pos.y());
                }
                if(flag_y == 2)//当猫触到屏幕上面面边框时向下移动
                {
                    this->m_Auto_Pos.setY(this->m_Auto_Pos.y()+4);
                }
            }
            else if(flag_x == 2)//猫位于左边向右移动
            {
                this->m_Auto_Pos.setX(this->m_Auto_Pos.x()+5);
                this->m_Auto_Pos.setY(this->m_Auto_Pos.y()-2);

                if(this->m_Auto_Pos.y() <= -this->height())
                {
                    flag_y = 2;//当猫y轴位于上面时，值为2
                }
                if(this->m_Auto_Pos.y() >= desk->height())
                {
                    flag_y = 1;//当猫y轴位于下面时，值为1
                }
                if(flag_y == 1)//当猫触到屏幕下面边框时向上移动
                {
                    this->m_Auto_Pos.setY(this->m_Auto_Pos.y());
                }
                if(flag_y == 2)//当猫触到屏幕上面面边框时向下移动
                {
                    this->m_Auto_Pos.setY(this->m_Auto_Pos.y()+4);
                }
            }

        }

        //窗口同步移动
        this->move(this->m_Auto_Pos);
    });

    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置透明窗体 120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口顶层
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);
    //设置起始Y位置
    this->m_Auto_Pos.setY(desk->height()*0.5-this->m_Cat->height()*0.5);
    //设置起始X位置
    this->m_Auto_Pos.setX(desk->width()*0.5-this->m_Cat->width()*0.5);

}
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->m_Cat->m_WhiteCat_Pix);
}

MainScene::~MainScene()
{
}

