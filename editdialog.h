#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>

class editdialog : public QDialog
{
    Q_OBJECT
public:
    explicit editdialog(QWidget *parent = nullptr);
    QSpinBox *width, *height, *radius,*radius2,*radius3, *cut,*cut2, *corner, *angle;
    QCheckBox *check_clock;
    QLineEdit *sq, *per;
    int sqr = 0,perr = 0;



};

#endif // EDITDIALOG_H
