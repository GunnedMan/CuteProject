#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QKeyEvent>
#include <QObject>

struct KeyHolder{
    int key;
    bool isPressed;
    int ticks;
};


class InputHandler : public QObject
{
    Q_OBJECT
public:
    explicit InputHandler(QObject *parent = nullptr);
    bool IsKeyPressed(Qt::Key key, int* timeMSec);
    void KeyPressEvent(QKeyEvent *event);
    void KeyReleaseEvent(QKeyEvent *event);
    void UpdateGame(int ticks = 1);

private:
    int GetKeyIndex(int key);
    int GetFreeIndex();
    int GetLongestIndex();


private:

    const int MaxKeys = 32;
    KeyHolder m_keys[32];

};











#endif // INPUTHANDLER_H
