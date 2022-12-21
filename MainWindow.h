#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "figure1.h"
#include "figure2.h"
#include "editdialog.h"
#include "angle.h"

#include <QMainWindow>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    QAction *quit, *button_fig_1, *button_fig_2, *add_fig_button,
    *delete_fig_button, *change_prop_button, *change_angle_button,
    *move_button, *delete_all;
    QMenu *mainmenu, *mainmenu_2;


    int timer;
    int prev_color1 = 0,prev_color2 = 0;
    int chosen1 = 1337, chosen2 = 1337;

    QVector <Figure1*> fig1_base;
    QVector <Figure2*> fig2_base;

    editdialog dialog;
    Angle slider_dialog;

    void button_check();
    void add_figure();
    void delete_figure();
    void show_dialog();
    void show_slider();
    void change_angle();
    void move_without();
    void delete_everything();



protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};
#endif // MAINWINDOW_H
