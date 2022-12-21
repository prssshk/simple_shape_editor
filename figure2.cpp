#include "figure2.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QtMath>
Figure2::Figure2(QWidget *parent) : QWidget(parent)
{

}

void Figure2::paintEvent(QPaintEvent *)
{
QPainterPath path;
QPainterPath path2;
path.moveTo(0-w/2,0-h/2);

path.lineTo(w/2-p/2-w/2,0-h/2);
    path.lineTo(w/2-p/2-w/2,p/2-h/2);
    path.lineTo(w/2+p/2-w/2,p/2-h/2);
    path.lineTo(w/2+p/2-w/2,0-h/2);
path.lineTo(w-w/2,0-h/2);
path.lineTo(w-w/2,h-r-h/2);
path.lineTo(w-r-w/2,h-h/2);
   path.addEllipse(w-w/2-2*r,h-r-h/2-r,2*r,2*r);
path.moveTo(w-r-w/2,h-h/2);
path.lineTo(w/2+p2/2-w/2,h-h/2);
    path.lineTo(w/2+p2/2-w/2,h-p2/2-h/2);
    path.lineTo(w/2-p2/2-w/2,h-p2/2-h/2);
    path.lineTo(w/2-p2/2-w/2,h-h/2);
path.lineTo(xx-w/2,h-h/2);
    path.lineTo(xx-w/2,h-xx-h/2);
    path.lineTo(0-w/2,h-xx-h/2);
path.lineTo(0-w/2,0-h/2);
path.setFillRule(Qt::WindingFill);
path2 = path.simplified();

pen.setWidth(1);
QPainter painter(this);

painter.setPen(pen);
painter.setBrush(Qt::SolidPattern);
painter.setBrush(Qt::red);
painter.translate(qSqrt(w*w+h*h)/2,qSqrt(w*w+h*h)/2);
painter.rotate(ang*cl);
painter.drawPath(path2);

}


void Figure2::change_color()
{
    pen.setColor(QColor(0,0,255));
    repaint();
}

void Figure2::change_color_back()
{
    pen.setColor(QColor(0,0,0));
    repaint();
}

void Figure2::change_position()
{
    int dif = qSqrt(w*w+h*h);
    int ww = QRandomGenerator::global()->generate()%(1280-dif)+10;
    int hh = QRandomGenerator::global()->generate()%(900-dif)+10;

    setGeometry(ww,hh,qSqrt(w*w+h*h),qSqrt(w*w+h*h));
}

void Figure2::change_properties(int wm, int hm, int rm, int pm, int xm, int pm2)
{
    w = wm;
    h = hm;
    r =rm;
    p = pm;
    p2 = pm2;
    xx = xm;
    repaint();
}

void Figure2::change_rotation(int angle)
{
    ang = angle;
    repaint();
}

void Figure2::change_size(int x, int y)
{
    setGeometry(x,y,qSqrt(w*w+h*h),qSqrt(w*w+h*h));
    repaint();
}

void Figure2::change_clockwise(int i)
{
   cl = i;
}

int Figure2::area()
{
    int area;
   // area = w*h-2*w*r-xx*xx-p*p-r*r+(3.1415*r*r)/4;
    area = w*h-p*p/2-xx*xx-p2*p2/2-3.1415*r*r/4;
    return area;
}

int Figure2::perimeter()
{
    int per;
    //per = 2*w+2*p-2*r+xx+(3.1415*r)/2;
    per = w+p+(h-r) + 2*3.1415*r/4+(w-r)+p2+xx+h;
    return per;
}

