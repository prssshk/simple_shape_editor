#ifndef FIGURE2_H
#define FIGURE2_H

#include <QWidget>
#include <QPen>


class Figure2 : public QWidget
{
    Q_OBJECT
public:
    explicit Figure2(QWidget *parent = nullptr);

    void change_color();
    void change_color_back();
    void change_position();
    void change_properties(int wm, int hm, int rm, int pm, int xm, int pm2);
    void change_rotation(int angle);
    void change_size(int x, int y);
    void change_clockwise(int i);
    int area();
    int perimeter();

    int w,h,p,p2,r,xx,ang,cl = 1;

private:


     QPen pen;

protected:
    void paintEvent(QPaintEvent *event);
signals:

};

#endif // FIGURE2_H
