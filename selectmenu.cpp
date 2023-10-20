#include "selectmenu.h"
#include "ui_selectmenu.h"

selectMenu::selectMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectMenu)
{
    ui->setupUi(this);
    setWindowTitle("选择导入选项");
    connect(ui->youdao,SIGNAL(clicked()),this,SLOT(youdao()));
    connect(ui->l1,SIGNAL(clicked()),this,SLOT(l1()));
    connect(ui->l2,SIGNAL(clicked()),this,SLOT(l2()));
    connect(ui->l3,SIGNAL(clicked()),this,SLOT(l3()));
}

selectMenu::~selectMenu()
{
    delete ui;
}

void selectMenu::youdao()
{
    QMessageBox::information(this,"注意","此选项导入的是有道词典的导出文件\n插入词组时可能会出现问题");
    QString filename = QFileDialog::getOpenFileName(this,tr("选择文件"),"/",tr("*.txt"));
    if(!filename.isEmpty()){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"无法打开文件\n";
        }else{
            char buffer[2048]={};
            int end=0;
            bool done=false;
            QString t_word,t_translation;
            //算是部分成功了吧
            while(end!=-1){
                end = file.readLine(buffer,2048);
                QString str=QString::fromUtf8(buffer);
                if(str.size()<3)continue;
                QRegExp qreg_word("[0-9]+,");
                QRegExp qreg_trans("[a-z]+.");
                if(qreg_word.indexIn(str)==0){
                    t_word=str.split(" ")[1];
                }
                else if(qreg_trans.indexIn(str)==0){
                    t_translation+=str;
                    t_translation+="\n";
                }else{
                    done=true;
                }
                if(done==true&&t_word.size()>0&&t_translation.size()>0){
                    FileSystem* f=FileSystem::getInstance();
                    if(f->insertData(t_word,t_translation)){
                        //想想怎么加
                    }else{
                        qDebug()<<"插入失败\n";
                    }
                    t_word.clear();
                    t_translation.clear();
                    done=false;
                }
            }
            QMessageBox::information(this,"提示","插入成功");
        }
    }
}

void selectMenu::l1()
{
    QMessageBox::information(this,"注意","单词[空格]翻译");
    QString filename = QFileDialog::getOpenFileName(this,tr("选择文件"),"/",tr("*.txt"));
    if(!filename.isEmpty()){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"无法打开文件\n";
        }else{
            char buffer[2048]={};
            int end=0;
            QString t_word,t_translation;
            while(end!=-1){
                end = file.readLine(buffer,2048);
                QString str=QString::fromUtf8(buffer);
                //if(str.size()<3)continue;
                t_word=str.split(" ")[0];
                t_translation=str.split(" ")[1];
                FileSystem* system=FileSystem::getInstance();
                if(system->insertData(t_word,t_translation)){

                }else{
                    qDebug()<<"插入失败";
                }
            }
            QMessageBox::information(this,"提示","插入成功");
        }
    }
}

void selectMenu::l2()
{
    QMessageBox::information(this,"注意","单词\n翻译");
    QString filename = QFileDialog::getOpenFileName(this,tr("选择文件"),"/",tr("*.txt"));
    if(!filename.isEmpty()){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"无法打开文件\n";
        }else{
            char buffer[2048]={};
            int end=0;
            bool done=false;
            QString t_word,t_translation;
            while(end!=-1){
                end = file.readLine(buffer,2048);
                QString str=QString::fromUtf8(buffer);
                //if(str.size()<3)continue;
                if(done){
                    t_word=str;
                    done=false;
                }else{
                    t_translation=str;
                    done=true;
                }
                FileSystem* system=FileSystem::getInstance();
                if(done){
                    if(system->insertData(t_word,t_translation)){

                    }else{
                        qDebug()<<"插入失败";
                    }
                }
            }
            QMessageBox::information(this,"提示","插入成功");
        }
    }
}

void selectMenu::l3()
{
//待定
}
