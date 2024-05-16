#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QWidget>

class TestObject : public QWidget
{
    Q_OBJECT
public:
    explicit TestObject(QWidget *parent = nullptr);

signals:

};

#endif // TESTOBJECT_H
