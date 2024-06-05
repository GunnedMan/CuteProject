#ifndef GMUIINDICATORBAR_H
#define GMUIINDICATORBAR_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QImage>

class GmUiIndicatorBar : public QWidget
{
    Q_OBJECT
public:
    explicit GmUiIndicatorBar(QWidget *parent = nullptr)
        :QWidget(parent)
    {
        
    }
    
signals:
    
    
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        QPainterPath path;
        path.addText()
    }
    
private:
    void invalidateGrafix()
    {
        m_pixImage = QImage(QSize(width(), height()), QImage::Format::Format_ARGB32);
        
    }
    
    
private:
    const QString
    
    QFont m_font = QFont("Arial", 8, 50, true);
    QString m_text = "Empty bar";
    QColor m_barBorderColor = Qt::black;
    QColor m_barFillColor = Qt::blue;
    QColor m_textBorderColor = Qt::black;
    QColor m_textFillColor = Qt::yellow;
    
    QImage m_pixImage;
    
};

#endif // GMUIINDICATORBAR_H
