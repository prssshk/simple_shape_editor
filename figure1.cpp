#include "figure1.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

Figure1::Figure1(QWidget *parent) : QWidget(parent)
{

}

void Figure1::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    QPainterPath path2;
    QPainterPath path3;

    path.setFillRule(Qt::WindingFill);

    path.moveTo(0-w/2,0-h/2);
    path.addRect(0-w/2,0-h/2,w-r2,h);
    path.addRect(0-w/2,r-h/2,w,h-2*r2);
    path.lineTo(w-w/2-r,0-h/2);
    path.lineTo(w-w/2,0+r-h/2);
        path3.addEllipse(w-w/2-r, 0-h/2-r, 2*r, 2*r);
        path.addEllipse(w-2*r-w/2, 0-h/2, 2*r, 2*r);
    path.moveTo(w-w/2,0+r-h/2);
    path.lineTo(w-w/2,h-r2-h/2);
    path.lineTo(w-r2-w/2,h-h/2);
        path.addEllipse(w-2*r2-w/2, h-2*r2-h/2, 2*r2, 2*r2);
    path.moveTo(w-r2-w/2,h-h/2);
    path.lineTo(r3-w/2,h-h/2);
     path.lineTo(0-w/2,h-r3-h/2);
        path.addEllipse(0-w/2, h-2*r3-h/2, 2*r3, 2*r3);
        path3.addEllipse(0-w/2-r3, h-h/2-r3, 2*r3, 2*r3);
    path.moveTo(0-w/2,h-r3-h/2);
    path.lineTo(0-w/2,0-h/2);

    path2 = path.subtracted(path3);

    pen.setWidth(1);
    QPainter painter(this);

    painter.setPen(pen);
    painter.setBrush(Qt::green);
    painter.translate(qSqrt(w*w+h*h)/2,qSqrt(w*w+h*h)/2);
    painter.rotate(ang*cl);
    painter.drawPath(path2);
}

void Figure1::change_color()
{
    pen.setColor(QColor(0,0,255));
    repaint();
}

void Figure1::change_color_back()
{
    pen.setColor(QColor(0,0,0));
    repaint();
}

void Figure1::change_position()
{
   int dif = qSqrt(w*w+h*h);
   int ww = QRandomGenerator::global()->generate()%(1280-dif)+10;
   int hh = QRandomGenerator::global()->generate()%(900-dif)+10;

   setGeometry(ww,hh,qSqrt(w*w+h*h),qSqrt(w*w+h*h));
}

void Figure1::change_properties(int wm, int hm, int rm, int rm2, int rm3)
{
    w = wm;
    h = hm;
    r =rm;
    r2 = rm2;
    r3 = rm3;
    repaint();
}

void Figure1::change_rotation(int angle)
{
    ang = angle;
    repaint();
}

void Figure1::change_size(int x, int y)
{
    setGeometry(x,y,qSqrt(w*w+h*h),qSqrt(w*w+h*h));
    repaint();
}

void Figure1::change_clockwise(int i)
{
   cl = i;
}

int Figure1::area()
{
    int area;
   //area = h*w-r*r-(3.1415*r*r)/4;
    area = w *(h-r) - 1/4*3.1415*r*r+(w-r2)*r3-1/4*3.1415*r3*r3+1/4*3.1415*r2*r2;
    return area;
}

int Figure1::perimeter()
{
    int per;
   // per = w*2-6*r+(3*3.1415*r)/2+2*h;
    per = (w-r) + 2*3.1415*r/4+(h-r-r2)+2*3.1415*r2-4+(w-r2-r3)+2*3.1415*r3/4+(h-r3);
    return per;
}










