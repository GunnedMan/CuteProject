#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p_game = new Game();
    //p_game->resize(50,50);
    setLayout(new QGridLayout(this));
    this->layout()->addWidget(p_game);
    p_game->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));
}

MainWindow::~MainWindow()
{
    delete ui;
}

