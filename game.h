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

#include <gamephysobject.h>
#include <gameship.h>

class Game : public QWidget
{
    Q_OBJECT

private:
    QTimer* p_mainTimer;
    QGraphicsScene* p_mainScene;
    QGraphicsView* p_mainView;
    GameShip* p_testShip;
    GameShip* p_testShip2;

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





signals:


};

#endif // GAME_H
