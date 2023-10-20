#include "mainwindow.h"

#include <QApplication>
#include <QSystemTrayIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSystemTrayIcon trayIcon(QIcon("test.png"),&w);
    trayIcon.show();
    //w.setSystemTrayIcon(trayIcon);
    QObject::connect(&trayIcon,&QSystemTrayIcon::activated,[&](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::Trigger){
            if(w.isVisible()){
                w.hide();
            }else{
                w.show();
            }
        }
    });
    w.move(1920-w.width(),0);
    w.show();
    return a.exec();
}
