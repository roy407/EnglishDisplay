#ifndef ADDNWWIDGET_H
#define ADDNWWIDGET_H

#include <QWidget>
#include "selectmenu.h"
#include "filesystem.h"
namespace Ui {
class addNWWidget;
}

class addNWWidget : public QWidget
{
    Q_OBJECT

public:
    explicit addNWWidget(QWidget *parent = nullptr);
    ~addNWWidget();
private slots:
    void Import();
    void BatchImport();
private:
    Ui::addNWWidget *ui;
};

#endif // ADDNWWIDGET_H
