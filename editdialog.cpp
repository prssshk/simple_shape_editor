#include "editdialog.h"
#include "MainWindow.h"
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QDialog>
#include <QCheckBox>


editdialog::editdialog(QWidget *parent) : QDialog(parent)
{
      QFrame *frame = new QFrame(this);
      frame->setFrameStyle(QFrame::Box | QFrame::Sunken);

      QLabel *LabelWidth = new QLabel("Width",frame);
      width              = new QSpinBox(frame);

      QLabel *LabelHeight = new QLabel("Height",frame);
      height            = new QSpinBox(frame);

      QLabel *LabelRadius = new QLabel("Radius",frame);
      radius            = new QSpinBox(frame);
      QLabel *LabelRadius2 = new QLabel("Radius2",frame);
      radius2            = new QSpinBox(frame);
      QLabel *LabelRadius3 = new QLabel("Radius3",frame);
      radius3            = new QSpinBox(frame);

      QLabel *LabelCut = new QLabel("Middle Cut",frame);
      cut              = new QSpinBox(frame);
      QLabel *LabelCut2 = new QLabel("Middle Cut2",frame);
      cut2             = new QSpinBox(frame);


      QLabel *LabelCorner = new QLabel("Corner",frame);
      corner             = new QSpinBox(frame);

      QLabel *LabelAngle = new QLabel("Angle",frame);
      angle             = new QSpinBox(frame);

      check_clock = new QCheckBox("Make clockwise", this);

      sq = new QLineEdit(this);
      per = new QLineEdit(this);
      sq->setText(QString("Area = %1").arg(sqr));
      per->setText(QString("Perimeter = %1").arg(perr));
      sq->setReadOnly(true);
      per->setReadOnly(true);

      QGridLayout *fl = new QGridLayout(frame);

       width->setRange(1, 1000);
       height->setRange(2, 1000);

        angle->setRange(0,359);

        width->setValue(1);
        height->setValue(1);
        radius->setMinimum(1);
        radius2->setMinimum(1);
        radius3->setMinimum(1);
        angle->setMinimum(1);
        corner->setMinimum(1);
        cut->setMinimum(1);
        cut2->setMinimum(1);

      fl->addWidget(LabelWidth,0,0);
      fl->addWidget(width,0,1);

      fl->addWidget(LabelHeight,1,0);
      fl->addWidget(height,1,1);

      fl->addWidget(LabelRadius,2,0);
      fl->addWidget(radius,2,1);

      fl->addWidget(LabelRadius2,3,0);
      fl->addWidget(radius2,3,1);

      fl->addWidget(LabelRadius3,4,0);
      fl->addWidget(radius3,4,1);

      fl->addWidget(LabelAngle,5,0);
      fl->addWidget(angle,5,1);

      fl->addWidget(LabelCut,6,0);
      fl->addWidget(cut,6,1);


      fl->addWidget(LabelCut2,7,0);
      fl->addWidget(cut2,7,1);

      fl->addWidget(LabelCorner,8,0);
      fl->addWidget(corner,8,1);

      fl->addWidget(check_clock,9,0);

      fl->addWidget(sq,10,0);
      fl->addWidget(per,11,0);

      frame->setLayout(fl);

      QPushButton *accept_button = new QPushButton(tr("Accept"),this);
      connect(accept_button,SIGNAL(clicked()),this,SLOT(accept()));

      QGridLayout *l = new QGridLayout(this);
      l->addWidget(frame,0,0);
      l->addWidget(accept_button,1,0);
      setLayout(l);
}
