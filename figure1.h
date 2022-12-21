#ifndef FIGURE1_H
#define FIGURE1_H

#include <QWidget>
#include <QPen>

class Figure1 : public QWidget
{
    Q_OBJECT
public:
    explicit Figure1(QWidget *parent = nullptr);
    void change_color();
    void change_color_back();
    void change_position();
    void change_properties(int wm, int hm, int rm, int rm2,int rm3);
    void change_rotation(int angle);
    void change_size(int x, int y);
    void change_clockwise(int i);
    int area();
    int perimeter();

    int w,h,r,r2,r3,ang,cl = 1;


private:



    QPen pen;

protected:
    void paintEvent(QPaintEvent *event);

signals:

};

#endif // FIGURE1_H
