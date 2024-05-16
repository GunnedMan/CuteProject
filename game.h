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

class Game : public QWidget
{
    Q_OBJECT

private:
    QTimer* p_mainTimer;
    QGraphicsScene* p_mainScene;
    QGraphicsView* p_mainView;


protected:

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;


public:
    explicit Game(QWidget *parent = nullptr);






signals:


};

#endif // GAME_H
