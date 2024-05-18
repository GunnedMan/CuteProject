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
    p_mainView->setRenderHint(QPainter::Antialiasing, true);
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
    p_mainTimer->blockSignals(true);
    //time
    quint64 currentMSec = QDateTime::currentDateTime().toMSecsSinceEpoch();
    quint64 mSecElapsed = currentMSec - m_lastMSec;
    if(mSecElapsed > 60)
        mSecElapsed = 60;
    m_lastMSec = currentMSec;
    //focus
    if(!hasFocus())
        setFocus();
    //input
    inputHandler->UpdateGame(mSecElapsed);

    //objects
    p_testShip->UpdateGame(mSecElapsed);
    p_testShip2->UpdateGame(mSecElapsed);
    //p_mainView->centerOn(p_testShip->pos() + p_testShip->velocityLin().toPointF());
    if(p_testShip != nullptr)
        p_mainView->centerOn(p_testShip->pos());
    //qDebug()<<QString("Pos: %1, %2").arg(p_testShip->x()).arg(p_testShip->y());
    p_mainTimer->blockSignals(false);

}

void Game::keyPressEvent(QKeyEvent *event)
{
    inputHandler->KeyPressEvent(event);
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    inputHandler->KeyReleaseEvent(event);
}

Game::Game(QWidget *parent) : QWidget(parent)
{
    p_mainScene = new QGraphicsScene(this);
    p_mainScene->setSceneRect(-100000, -100000, 100000*2, 100000*2);

    inputHandler = new InputHandler(this);

    p_mainTimer = new QTimer(this);
    p_mainView = new QGraphicsView(this);

    p_testShip = new GameShip(p_mainScene);
    p_testShip2 = new GameShip(p_mainScene);
    p_testShip->setPos(200, 100);
    p_testShip->SetInput(inputHandler);
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
