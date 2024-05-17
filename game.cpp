#include "game.h"


void Game::InitLayout()
{
    QGridLayout* gl = new QGridLayout(this);
    setLayout(gl);
    gl->setMargin(0);
    layout()->addWidget(p_mainView);
}

void Game::InitGraphics()
{
    p_mainView->setScene(p_mainScene);
    //p_mainView->fitInView(QRectF(-50, -50, 100, 100));
    p_mainView->scale(1,1);
}

void Game::InitInput()
{

}

void Game::InitTimer()
{
    p_mainTimer->setInterval(1000/60);
    connect(p_mainTimer, &QTimer::timeout, this, &Game::Update);
    p_mainTimer->start();
}

void Game::Update()
{
    if(!hasFocus())
        setFocus();

    p_testShip->UpdateGame();
    p_testShip2->UpdateGame();
    p_mainView->centerOn(p_testShip->pos() + p_testShip->velocityLin().toPointF());


}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        p_testShip->SetThrustMain(200);
        break;
    case Qt::Key_Down:
        p_testShip->SetThrustMain(-200);
        break;
    case Qt::Key_Left:

        p_testShip->SetThrustRot(-100000);
        break;
    case Qt::Key_Right:
        p_testShip->SetThrustRot(100000);
        break;
    case Qt::Key_Q:

        break;
    case Qt::Key_E:

        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }



}

void Game::keyReleaseEvent(QKeyEvent *event)
{

    QWidget::keyReleaseEvent(event);
}

Game::Game(QWidget *parent) : QWidget(parent)
{
    p_mainScene = new QGraphicsScene(this);
    p_mainScene->setSceneRect(-100000, -100000, 100000*2, 100000*2);


    p_mainTimer = new QTimer(this);
    p_mainView = new QGraphicsView(this);

    p_testShip = new GameShip(this);
    p_testShip2 = new GameShip(this);
    p_testShip->setPos(100, 100);
    p_testShip2->setPos(100, 0);

    InitLayout();
    InitGraphics();
    InitTimer();


    p_mainScene->addItem(p_testShip);
    p_mainScene->addItem(p_testShip2);



}

QGraphicsView *Game::View()
{
    return p_mainView;
}
