#include "addnwwidget.h"
#include "ui_addnwwidget.h"

addNWWidget::addNWWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addNWWidget)
{
    ui->setupUi(this);
    setWindowTitle("导入单词");
    connect(ui->Import,SIGNAL(clicked()),this,SLOT(Import()));
    connect(ui->BatchImport,SIGNAL(clicked()),this,SLOT(BatchImport()));
}

addNWWidget::~addNWWidget()
{
    delete ui;
}

void addNWWidget::Import()
{
    QString word=ui->word->toPlainText();
    QString translation=ui->translation->toPlainText();
    if(word.size()==0||translation.size()==0){
        QMessageBox::information(this,"提示","输入不完整");
        return;
    }
    FileSystem* f=FileSystem::getInstance();
    if(f->insertData(word,translation)){
        QMessageBox::information(this,"提示","插入成功");
    }else{
        QMessageBox::information(this,"提示","插入失败");
    }
}

void addNWWidget::BatchImport()
{
    selectMenu* select=new selectMenu();
    select->show();
}
