#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QScreen>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QSystemTrayIcon>
#include "filesystem.h"
#include "addnwwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    template<typename T>
    void initMenu(T&t);
    void drawBackground();
    void reset();
    void setSystemTrayIcon(QSystemTrayIcon& trayIcon);
//event
    void timerEvent(QTimerEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void insertNWWidget();
    void deleteAll();
    void deleteW();
private:
    Ui::MainWindow *ui;
    bool m_drag;
    QMenu* menu;
    FileSystem* fsystem;
    QList<QPair<QString,QString>> t;
};
#endif // MAINWINDOW_H
