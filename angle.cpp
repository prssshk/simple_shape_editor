#include "angle.h"
#include "MainWindow.h"

#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>

Angle::Angle(QWidget *parent) : QWidget(parent)
{
    QFrame *frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Box | QFrame::Sunken);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(-180, 180);
    slider->setTickPosition(QSlider::TicksBothSides);

    QGridLayout *fl = new QGridLayout(frame);
    fl->addWidget(slider,0,0);

    QGridLayout *l = new QGridLayout(this);
    l->addWidget(frame,0,0);
    setLayout(l);

}


