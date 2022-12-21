#include "MainWindow.h"
#include "figure1.h"
#include "figure2.h"
#include "editdialog.h"
#include "angle.h"

#include <QApplication>
#include <QToolBar>
#include <QMouseEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    connect(slider_dialog.slider, &QSlider::valueChanged, this,
            &MainWindow::change_angle );

                    //TOOLBAR
    QToolBar *toolbar = addToolBar("main");

//    quit = new QAction("Quit", this);
//    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
//    toolbar->addAction(quit);

    button_fig_1 = new QAction("Figure 1", this);
    toolbar->addAction(button_fig_1);
    button_fig_1->setCheckable(true);

    button_fig_2 = new QAction("Figure 2", this);
    toolbar->addAction(button_fig_2);
    button_fig_2->setCheckable(true);

    add_fig_button = new QAction("Add", this);
    connect(add_fig_button, &QAction::triggered, this,
            &MainWindow::add_figure);
    toolbar->addAction(add_fig_button);

    delete_fig_button = new QAction("Delete", this);
    connect(delete_fig_button, &QAction::triggered, this,
            &MainWindow::delete_figure);
    toolbar->addAction(delete_fig_button);

    change_prop_button = new QAction("Change", this);
    connect(change_prop_button, &QAction::triggered, this,
            &MainWindow::show_dialog);

    change_angle_button = new QAction("Change Angle", this);
    connect(change_angle_button, &QAction::triggered, this,
            &MainWindow::show_slider);

    move_button = new QAction("Move", this);
    connect(move_button, &QAction::triggered, this,
            &MainWindow::move_without);

    delete_all = new QAction("Delete All", this);
    connect(delete_all, &QAction::triggered, this,
            &MainWindow::delete_everything);

    mainmenu=menuBar()->addMenu("menu_figure");
    mainmenu->menuAction()->setVisible(false);
    mainmenu->addAction(delete_fig_button);
    mainmenu->addAction(change_prop_button);
    mainmenu->addAction(change_angle_button);
    mainmenu->addAction(move_button);

    mainmenu_2= menuBar()->addMenu("menu");
    mainmenu_2->menuAction()->setVisible(false);
    mainmenu_2->addAction(delete_all);

    setFixedSize(1280,900);

    timer = startTimer(50);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void MainWindow::button_check()
{
    if (fig1_base.size() == 0 && fig2_base.size() == 0)
        delete_fig_button->setDisabled(true);
    else
        delete_fig_button->setDisabled(false);

    if (button_fig_1->isChecked() || button_fig_2->isChecked())
        add_fig_button->setDisabled(false);
    else
         add_fig_button->setDisabled(true);

    if (button_fig_1->isChecked())
        button_fig_2->setDisabled(true);
    else
        button_fig_2->setDisabled(false);

    if (button_fig_2->isChecked())
        button_fig_1->setDisabled(true);
    else
        button_fig_1->setDisabled(false);
}

void MainWindow::show_dialog()
{
    if (chosen1  != 1337)
    {
        dialog.width->setValue(fig1_base[chosen1]->w);
        dialog.height->setValue(fig1_base[chosen1]->h);
        dialog.radius->setValue(fig1_base[chosen1]->r);
         dialog.radius2->setValue(fig1_base[chosen1]->r2);
          dialog.radius3->setValue(fig1_base[chosen1]->r3);
        dialog.angle->setValue(fig1_base[chosen1]->ang);
        dialog.sq->setText(QString("Area = %1").arg(fig1_base[chosen1]->area()));
        dialog.per->setText(QString("Perimeter = %1").arg(
                                fig1_base[chosen1]->perimeter()));
        dialog.cut->setVisible(false);
        dialog.cut2->setVisible(false);
        dialog.corner->setVisible(false);
        dialog.radius2->setVisible(true);
        dialog.radius3->setVisible(true);
    }
    if (chosen2 != 1337)
    {
        dialog.width->setValue(fig2_base[chosen2]->w);
        dialog.height->setValue(fig2_base[chosen2]->h);
        dialog.radius->setValue(fig2_base[chosen2]->r);
        dialog.angle->setValue(fig2_base[chosen2]->ang);
        dialog.cut->setValue(fig2_base[chosen2]->p);
        dialog.cut2->setValue(fig2_base[chosen2]->p2);
        dialog.corner->setValue(fig2_base[chosen2]->xx);
        dialog.sq->setText(QString("Area = %1").arg(fig2_base[chosen2]->area()));
        dialog.per->setText(QString("Perimeter = %1").arg(
                                fig2_base[chosen2]->perimeter()));
        dialog.cut->setVisible(true);
        dialog.cut2->setVisible(true);
        dialog.corner->setVisible(true);
        dialog.radius2->setVisible(false);
        dialog.radius3->setVisible(false);

    }

    int wm,hm,rm,rm2,rm3,pm,pm2,xm,angle,i = 1;
    if (dialog.exec() == QDialog::Accepted)
    {
        if (chosen1 != 1337)
        {
            wm = dialog.width->value();
            hm = dialog.height->value();
            rm = dialog.radius->value();
            angle = dialog.angle->value();
            rm2 = dialog.radius2->value();
            rm3 = dialog.radius3->value();
            if (dialog.check_clock->isChecked())
                i = -1;
            if (hm >wm)
                hm = wm -1;
            if(rm > hm/3)
                rm = hm/3-1;
            if(rm2 > hm/3)
                rm2 = hm/3-1;
            if(rm3 > hm/3)
                rm3 = hm/3-1;

            fig1_base[chosen1]->change_clockwise(i);
            fig1_base[chosen1]->change_properties(wm,hm,rm,rm2,rm3);
            fig1_base[chosen1]->change_size(fig1_base[chosen1]->x(),
                                            fig1_base[chosen1]->y());
            fig1_base[chosen1]->change_rotation(angle);
        }

        if (chosen2 != 1337)
        {
            wm = dialog.width->value();
            hm = dialog.height->value();
            rm = dialog.radius->value();
            angle = dialog.angle->value();
            pm = dialog.cut->value();
            pm2 = dialog.cut2->value();
            xm = dialog.corner -> value ();
            if (dialog.check_clock->isChecked())
                i = -1;

            if (hm >wm)
                hm = wm -1;
            if(rm > hm/3)
                rm = hm/3-1;
            if (xm > wm/2+pm/2)
                xm = wm/2+pm/2 -1;
            if (pm > hm/3)
                pm = hm/3-1;
            if (pm2 > hm/3)
                pm2 = hm/3-1;

            fig2_base[chosen2]->change_clockwise(i);
            fig2_base[chosen2]->change_properties(wm,hm,rm,pm,xm,pm2);
            fig2_base[chosen2]->change_size(fig2_base[chosen2]->x(),
                                            fig2_base[chosen2]->y());
            fig2_base[chosen2]->change_rotation(angle);
        }
    }
}

void MainWindow::show_slider()
{
    slider_dialog.show();
}

void MainWindow::delete_everything()
{
    while (fig1_base.size()!=0)
    {
        fig1_base[fig1_base.size()-1]->deleteLater();
        fig1_base.remove(fig1_base.size()-1);
        prev_color1 = 0;
        chosen1 = 1337;
    }
    while (fig2_base.size()!=0)
    {
        fig2_base[fig2_base.size()-1]->deleteLater();
        fig2_base.remove(fig2_base.size()-1);
        prev_color2 = 0;
        chosen2 = 1337;
    }
}

void MainWindow::move_without()
{
   setMouseTracking(true);
}

void MainWindow::   change_angle()
{
    if (chosen1 != 1337)
        fig1_base[chosen1]->change_rotation(slider_dialog.slider->value());
    if (chosen2 != 1337)
        fig2_base[chosen2]->change_rotation(slider_dialog.slider->value());

}

void MainWindow::add_figure()
{
    int wm,hm,rm,rm2,rm3,pm,pm2,xm,angle;
    if (button_fig_1->isChecked())
    {
        fig1_base << (new Figure1(this));

        wm = QRandomGenerator::global()->generate()%250;
        hm = QRandomGenerator::global()->generate()%wm;
        rm = QRandomGenerator::global()->generate()%hm/3;
        rm2 = QRandomGenerator::global()->generate()%hm/3;
        rm3 = QRandomGenerator::global()->generate()%hm/3;
        wm = wm % 250 +15;
        hm = hm % wm +10;
        rm = rm % (hm/3) +3 ;
        rm2 = rm2 % (hm/3) +3 ;
        rm3 = rm3 % (hm/3) +3 ;

        angle = QRandomGenerator::global()->generate()%359;

        fig1_base[fig1_base.size()-1]->change_properties(wm,hm,rm,rm2,rm3);
        fig1_base[fig1_base.size()-1]->change_position();
        fig1_base[fig1_base.size()-1]->change_rotation(angle);
        fig1_base[fig1_base.size()-1]->show();

    }
    if (button_fig_2->isChecked())
    {
        fig2_base<< (new Figure2(this));

        wm = QRandomGenerator::global()->generate()%250+50;
        hm = QRandomGenerator::global()->generate()%wm+30;
        pm = QRandomGenerator::global()->generate()%hm/3+10;
        pm2 = QRandomGenerator::global()->generate()%hm/3+8;
        rm = QRandomGenerator::global()->generate()%(hm/3)+1;
        xm = QRandomGenerator::global()->generate()%hm/4+3;
        angle = QRandomGenerator::global()->generate()%359;
        xm = xm % (wm/2+pm/2);

        fig2_base[fig2_base.size()-1]->change_properties(
                    wm,hm,rm%((wm/2+pm/2))/2,pm%(hm/3),xm%(wm/2+pm/2), pm2%(hm/3));
        fig2_base[fig2_base.size()-1]->change_position();
        fig2_base[fig2_base.size()-1]->change_rotation(angle);
        fig2_base[fig2_base.size()-1]->show();
    }
}

void MainWindow::delete_figure()
{
    if ( chosen1 !=1337)
    {

        fig1_base[chosen1]->deleteLater();
        fig1_base.remove(chosen1);
        prev_color1 = 0;
        chosen1 = 1337;
    }
    if ( chosen2 != 1337)
    {

        fig2_base[chosen2]->deleteLater();
        fig2_base.remove(chosen2);
        prev_color2 = 0 ;
        chosen2 = 1337;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
                //CHANGING CURSOR
    if (event->button() == Qt::LeftButton)
        this->setCursor(QCursor(Qt::ClosedHandCursor));

                //FINDING POS OF CURSOR ACCORDING FIGURES
    for (int i =fig1_base.size()-1;i>=0;i--)
    {
        if (fig1_base[i]->geometry().contains(
                    event->pos()) && fig1_base[i]->grab(
                    QRect(1,1,fig1_base[i]->width(),fig1_base[i]->height())
                    ).toImage().pixelColor(event->pos().x()
                                           -fig1_base[i]->x(),event->pos().y()
                                           -fig1_base[i]->y()) == QColor(0,255,0))
        {
            chosen1 = i;
            break;

        }
    }

    for (int i =fig2_base.size()-1;i>=0;i--)
    {
        if (fig2_base[i]->geometry().contains(
                    event->pos())&& fig2_base[i]->grab(
                    QRect(1,1,fig2_base[i]->width(),fig2_base[i]->height())
                    ).toImage().pixelColor(event->pos().x()
                                           -fig2_base[i]->x(),event->pos().y()
                                           -fig2_base[i]->y()) == QColor(255,0,0))
        {
            chosen2 = i;
            break;
        }
    }

                //FIGURE 1 CHOOSING
    if ( chosen1 != 1337 && fig1_base[chosen1]->geometry().contains(event->pos()))

    {
        if ( fig1_base.size()!=0)
        {
            if (chosen1 != prev_color1 )
                fig1_base[prev_color1]->Figure1::change_color_back();
        }

            if (fig2_base.size()!=0)
                fig2_base[prev_color2]->Figure2::change_color_back();

            fig1_base[chosen1]->Figure1::change_color();
            prev_color1 = chosen1;
            setMouseTracking(false);

    }

    if ( chosen1 != 1337 && (
             !fig1_base[chosen1]->geometry().contains(event->pos())
             || fig1_base[chosen1]->grab(
                 QRect(1,1,fig1_base[chosen1]->width(),
                       fig1_base[chosen1]->height())
                 ).toImage().pixelColor(event->pos().x()
                  -fig1_base[chosen1]->x(),event->pos().y()
                  -fig1_base[chosen1]->y()) != QColor(0,255,0)))
    {
        fig1_base[chosen1]->Figure1::change_color_back();
        chosen1 = 1337;
        setMouseTracking(false);
    }

               //FIGURE 2 CHOOSING
    if ( chosen2 != 1337 && fig2_base[chosen2]->geometry().contains(event->pos()) )

    {
        if (fig2_base.size()!=0)
        {
            if (chosen2 != prev_color2)
            fig2_base[prev_color2]->Figure2::change_color_back();
        }
            if (fig1_base.size()!=0)
                fig1_base[prev_color1]->Figure1::change_color_back();

            fig2_base[chosen2]->Figure2::change_color();
            prev_color2 = chosen2;
            setMouseTracking(false);
    }
    if ( chosen2 != 1337 && (
             !fig2_base[chosen2]->geometry().contains(event->pos())
             || fig2_base[chosen2]->grab(
                 QRect(1,1,fig2_base[chosen2]->width(),
                       fig2_base[chosen2]->height())
                 ).toImage().pixelColor(event->pos().x()
                   -fig2_base[chosen2]->x(),event->pos().y()
                   -fig2_base[chosen2]->y()) != QColor(255,0,0)))
    {
        fig2_base[chosen2]->Figure2::change_color_back();
        chosen2 =1337;
        setMouseTracking(false);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{

        this->setCursor(QCursor(Qt::ArrowCursor));
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

                //FIGURE1_MOVING
    if (chosen1 != 1337  )
    {
        int difx = (fig1_base[chosen1]->width())/2;
        int dify = fig1_base[chosen1]->height()/2;
        fig1_base[chosen1]->move(event->pos().x()-difx,event->pos().y()-dify);

        if (event->pos().x() <= -5+difx   )
        {
            if (event->pos().y()<=30+dify)
                fig1_base[chosen1]->move(-5 ,45);
            else if (event->pos().y()>=(900-fig1_base[chosen1]->height()+5)+dify)
                fig1_base[chosen1]->
                        move(-5-difx ,(900-fig1_base[chosen1]->height()+5));
            else
                fig1_base[chosen1]->move(-5 ,event->windowPos().y()-dify);
        }

        if (event->pos().x() >= (1280-fig1_base[chosen1]->width()+5+difx))
        {
            if (event->pos().y()<=30+dify)
                fig1_base[chosen1]->move((1280-fig1_base[chosen1]->width()+5),30);
            else if (event->pos().y()>=(900-fig1_base[chosen1]->height()+5+dify))
                fig1_base[chosen1]->
                        move((1280-fig1_base[chosen1]->
                              width()+5),(900-fig1_base[chosen1]->height()+5));
            else
                fig1_base[chosen1]->move(
                            (1280-fig1_base[chosen1]->width()+5),
                            event->windowPos().y()-dify);
        }

        if (event->pos().y() <= 30+dify )
        {
            if (event->pos().x()<=-5+difx)
                fig1_base[chosen1]->move(-5,30);
            else if (event->pos().x()>=(1280-fig1_base[chosen1]->width()+5+difx))
                fig1_base[chosen1]->move((1280-fig1_base[chosen1]->width()+5),30);
            else
            fig1_base[chosen1]->move(event->windowPos().x()-difx,30);
        }

        if (event->pos().y()>= (900-fig1_base[chosen1]->height()+5)+dify)
        {
            if (event->pos().x()<=-5+difx)
                fig1_base[chosen1]->move(-5,(900-fig1_base[chosen1]->height()+5));
            else if (event->pos().x()>=(1280-fig1_base[chosen1]->width()+5+difx))
                fig1_base[chosen1]->move(
                            (1280-fig1_base[chosen1]->width()+5),
                            (900-fig1_base[chosen1]->height()+5));
            else
                fig1_base[chosen1]->move(
                            event->windowPos().x()-difx,
                            (900-fig1_base[chosen1]->height()+5));
        }
    }

                    //FIGURE2_MOVING
    if ( chosen2 != 1337)
    {

        fig2_base[chosen2]->
                move(event->pos().x()-
                     (fig2_base[chosen2]->width())/2,
                        event->pos().y()-(fig2_base[chosen2]->height())/2);


        int difx = fig2_base[chosen2]->width()/2;
        int dify = fig2_base[chosen2]->height()/2;
        if (event->pos().x() <= -5+difx   )
        {
            if (event->pos().y()<=30+dify)
                fig2_base[chosen2]->move(-5 ,30);
            else if (event->pos().y()>=(900-fig2_base[chosen2]->height()+5)+dify)
                fig2_base[chosen2]->move(-5-difx ,
                                         (900-fig2_base[chosen2]->height()+5));
            else
                fig2_base[chosen2]->move(-5 ,event->windowPos().y()-dify);
        }

        if (event->pos().x() >= (1280-fig2_base[chosen2]->width()+5+difx))
        {
            if (event->pos().y()<=30+dify)
                fig2_base[chosen2]->move((1280-fig2_base[chosen2]->width()+5),30);
            else if (event->pos().y()>=(900-fig2_base[chosen2]->height()+5+dify))
                fig2_base[chosen2]->move(
                            (1280-fig2_base[chosen2]->width()+5),
                            (900-fig2_base[chosen2]->height()+5));
            else
                fig2_base[chosen2]->move(
                            (1280-fig2_base[chosen2]->width()+5),
                            event->windowPos().y()-dify);
        }

        if (event->pos().y() <= 30+dify )
        {
            if (event->pos().x()<=-5+difx)
                fig2_base[chosen2]->move(-5,30);
            else if (event->pos().x()>=(1280-fig2_base[chosen2]->width()+5+difx))
                fig2_base[chosen2]->move((1280-fig2_base[chosen2]->width()+5),30);
            else
            fig2_base[chosen2]->move(event->windowPos().x()-difx,30);
        }

        if (event->pos().y()>= (900-fig2_base[chosen2]->height()+5)+dify)
        {
            if (event->pos().x()<=-5+difx)
                fig2_base[chosen2]->move(-5,(900-fig2_base[chosen2]->height()+5));
            else if (event->pos().x()>=(
                         1280-fig2_base[chosen2]->width()
                         +5+difx))
                fig2_base[chosen2]->move(
                            (1280-fig2_base[chosen2]->width()+5),
                            (900-fig2_base[chosen2]->height()+5));
            else
                fig2_base[chosen2]->move(
                            event->windowPos().x()-difx,
                            (900-fig2_base[chosen2]->height()+5));
        }
    }

}

void MainWindow::timerEvent(QTimerEvent *)
{
    button_check();
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    if (chosen1 !=1337 && fig1_base[chosen1]->geometry().
            contains(event->pos()))
        mainmenu->exec(event->globalPos());
    else if (chosen2 !=1337 && fig2_base[chosen2]->
             geometry().contains(event->pos()))
        mainmenu->exec(event->globalPos());
    else
        mainmenu_2->exec(event->globalPos());
}
MainWindow::~MainWindow()
{
}

