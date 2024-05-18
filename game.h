#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QSizePolicy>
#include <QLayout>
#include <QTime>
#include <QDateTime>
#include <QtDebug>


#include <gamephysobject.h>
#include <gameship.h>
#include <inputhandler.h>

class Game : public QWidget
{
    Q_OBJECT

private:
    void InitLayout();
    void InitGraphics();
    void InitTimer();
    void Update();
    void InitInput();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;


public:
    explicit Game(QWidget *parent = nullptr);
    QGraphicsView* View();





private:
    QTimer* p_mainTimer;
    InputHandler* inputHandler;
    QGraphicsScene* p_mainScene;
    QGraphicsView* p_mainView;
    GameShip* p_testShip;
    GameShip* p_testShip2;
    quint64 m_lastMSec;



signals:


};

#endif // GAME_H
