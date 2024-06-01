#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QGridLayout* gl = new QGridLayout(this);




    centralWidget()->setLayout(gl);
    gl->setMargin(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

