#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);//去掉标题栏
    //setAttribute(Qt::WA_TranslucentBackground, true);//设置窗口背景透明
    this->statusBar()->setSizeGripEnabled(false);//隐去右下角拖动小图标
    setContextMenuPolicy(Qt::ActionsContextMenu);
    //菜单
    initMenu<MainWindow>(*this);
    //背景
    QHBoxLayout* layout=new QHBoxLayout();
    layout->addWidget(ui->label);
    layout->addWidget(ui->label_2);
    fsystem=FileSystem::getInstance();
    startTimer(10*1000);
    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}
template<typename T>
void MainWindow::initMenu(T& t)
{
    menu=new QMenu(this);
    QAction* addfile=new QAction("添加单词");
    QAction* deletefile=new QAction("删除单词");
    QAction* deleteAll=new QAction("删除全部");
    menu->addAction(addfile);
    menu->addAction(deletefile);
    menu->addAction(deleteAll);
    connect(addfile,SIGNAL(triggered()),this,SLOT(insertNWWidget()));
    connect(deletefile,SIGNAL(triggered()),this,SLOT(deleteW()));
    connect(deleteAll,SIGNAL(triggered()),this,SLOT(deleteAll()));
}

void MainWindow::drawBackground()
{
    QScreen* screen=QGuiApplication::primaryScreen();
    QPixmap pixmap=screen->grabWindow(0,x(),y(),width(),height());
    QImage background=pixmap.toImage();
    QBrush* b=new QBrush(background);
    QPalette pa(this->palette());
    pa.setBrush(QPalette::Window,*b);
    this->setPalette(pa);
}

void MainWindow::reset()
{
    t=fsystem->selectAll();
    if(t.size()!=0){
        setAttribute(Qt::WA_TranslucentBackground);
        ui->label->setText(t[0].first);
        ui->label_2->setText(t[0].second);
    }else{
        this->show();
    }
}

void MainWindow::setSystemTrayIcon(QSystemTrayIcon &trayIcon)
{
    menu=new QMenu();
    QAction* addfile=new QAction("添加单词");
    QAction* deletefile=new QAction("删除单词");
    QAction* deleteAll=new QAction("删除全部");
    menu->addAction(addfile);
    menu->addAction(deletefile);
    menu->addAction(deleteAll);
    connect(addfile,SIGNAL(triggered()),this,SLOT(insertNWWidget()));
    connect(deletefile,SIGNAL(triggered()),this,SLOT(deleteW()));
    connect(deleteAll,SIGNAL(triggered()),this,SLOT(deleteAll()));
    trayIcon.setContextMenu(menu);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    t=fsystem->selectAll();
    if(t.size()==0)return;
    static int index=1;
    if(t.size()<2)index=0;
    ui->label->setText(t[index].first);
    ui->label_2->setText(t[index].second);
    index++;
    if(index==t.size()){
        index=0;
        t=fsystem->selectAll();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        this->m_drag=true;
    }else if(event->button() == Qt::RightButton){
        menu->exec(QCursor::pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastpos(event->globalPos());
    if(this->m_drag==true){
        QRect m = this->geometry();
        QPoint n = event->globalPos();
        int x=m.x()+n.x()-lastpos.x();
        int y=m.y()+n.y()-lastpos.y();
        move(x,y);
        lastpos=n;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        this->m_drag=false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    //drawBackground();出问题
}

void MainWindow::insertNWWidget()
{
    //为何加入父类指针后，窗口反而显示不出来了
    addNWWidget* t1=new addNWWidget();
    t1->show();
    reset();
}

void MainWindow::deleteAll()
{
    int result=QMessageBox::information(this,"警告","您正在删除所有单词，是否继续？",QMessageBox::Ok | QMessageBox::Cancel);
    if(result==QMessageBox::Ok){
        fsystem->deleteAll();
        reset();
    }
}

void MainWindow::deleteW()
{
    QString str=QInputDialog::getText(this,"删除单词","输入");
    if(true){
        fsystem->deleteData(str);
        QMessageBox::information(NULL,"提示","删除成功");
    }
}

