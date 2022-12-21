#ifndef ANGLE_H
#define ANGLE_H

#include <QWidget>
#include <QSlider>

class Angle : public QWidget
{
    Q_OBJECT
public:
    explicit Angle(QWidget *parent = nullptr);
    QSlider *slider;


};

#endif // ANGLE_H
