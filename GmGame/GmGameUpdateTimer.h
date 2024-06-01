#ifndef GMGAMEUPDATETIMER_H
#define GMGAMEUPDATETIMER_H

#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include <QDateTime>


class GmGameUpdateTimer : public QObject
{
    Q_OBJECT
public:
    GmGameUpdateTimer(QObject* parent = nullptr, int fps = 60)
        : QObject(parent)
    {
        m_timer = new QTimer(this);
        setFps(fps);
        connect(m_timer, &QTimer::timeout, this, &GmGameUpdateTimer::onTimerTimeout);
    }

    inline void setFps(int value)
    {
        if(value > 0)
            m_fps = value;
        m_timer->setInterval(1000/m_fps);
    }

    inline float getFps() const
    {
        return m_currFps;
    }

    inline void start()
    {
        m_lastTimestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
        m_timer->start();
    }

    inline void stop()
    {
        m_timer->stop();
    }

protected:
    void onTimerTimeout()
    {
        uint timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
        uint delta = timestamp - m_lastTimestamp;
        m_currFps = delta / 1000.0f;
        if(delta > MaxElapsedMillis)
            delta = MaxElapsedMillis;
        m_lastTimestamp = timestamp;
        Timeout((int)delta);
    }

private:
    uint MaxElapsedMillis = 200;

    QTimer* m_timer;
    int m_fps;
    uint m_lastTimestamp;
    float m_currFps;

signals:
    void Timeout(int elapsedMillis);

};

#endif // GMGAMEUPDATETIMER_H
