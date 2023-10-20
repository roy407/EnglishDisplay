#ifndef SELECTMENU_H
#define SELECTMENU_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "filesystem.h"
namespace Ui {
class selectMenu;
}

class selectMenu : public QWidget
{
    Q_OBJECT

public:
    explicit selectMenu(QWidget *parent = nullptr);
    ~selectMenu();
private slots:
    void youdao();
    void l1();
    void l2();
    void l3();
private:
    Ui::selectMenu *ui;
};

#endif // SELECTMENU_H
