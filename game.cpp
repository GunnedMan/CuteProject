#include "game.h"


void Game::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

}

void Game::keyReleaseEvent(QKeyEvent *event)
{

    QWidget::keyReleaseEvent(event);
}

Game::Game(QWidget *parent) : QWidget(parent)
{
    p_mainScene = new QGraphicsScene(this);

    p_mainTimer = new QTimer(this);
    p_mainView = new QGraphicsView(this);
    p_mainView->setScene(p_mainScene);


    p_mainScene->addWidget(new QPushButton());
    p_mainView->ensureVisible(QRectF(-500,-500,1000,1000), 500, 500);

    //p_mainView->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));

    p_mainTimer->setInterval(20);



}
