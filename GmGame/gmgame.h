#ifndef GMGAME_H
#define GMGAME_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QSizePolicy>
#include <QLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QDateTime>
#include <QtDebug>

//GM includes
#include <GmGame/GmGameUpdateTimer.h>
#include <GmGame/GmGrafix/GmModel2D.h>
#include <GmGame/GmInput/GmInput.h>
#include <GmGame/GmPhysObject/GmPhysObject.h>
#include <GmGame/GmPhysObject/GmPlayerShip.h>

class GmGame : public QWidget
{
    Q_OBJECT

public:
    explicit GmGame(QWidget *parent = nullptr)
    : QWidget(parent)
    {
        p_mainTimer = new GmGameUpdateTimer(this);


    }

    QGraphicsView* View();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
    void InitLayout()
    {
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setParent(this);
        layout->setMargin(0);
        setLayout(layout);

    }

    void InitGraphics();
    void InitTimer();
    void Update();
    void InitInput();






private:
    GmGameUpdateTimer* p_mainTimer;
    GmInput* inputHandler;
    QGraphicsScene* p_mainScene;
    QGraphicsView* p_mainView;
    GmPlayerShip* p_testShip;
    GmPlayerShip* p_testShip2;
    quint64 m_lastMSec;



signals:


};

#endif // GMGAME_H
