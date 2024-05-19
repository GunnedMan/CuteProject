#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    p_game = new Game(this);
    QGridLayout* gl = new QGridLayout(this);
    centralWidget()->setLayout(gl);
    gl->addWidget(p_game, 0, 0, 1, 1);
    gl->setMargin(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

