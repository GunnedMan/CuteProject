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
        resize(30, 200);
    }
    
    void setMaxValue(int value)
    {
        if(value > 0)
            m_maxValue = value;
    }
    
    void setValue(int value)
    {
        if(value < 0)
        {
            m_value = 0;
            return;
        }
        if(value > m_maxValue)
        {
            m_value = m_maxValue;
            return;
        }
        m_value = value;
    }
    
    void setCaptionText(QString text)
    {
        m_captionText = text;
    }
    
    int value() const
    {
        return m_value;
    }
    
    int maxValue() const
    {
        return m_maxValue;
    }
    
    void setBarColor(QColor color)
    {
        m_barFillColor = color;
        m_barBorderColor = color.darker();
    }
    
    void setTextColor(QColor color)
    {
        m_textFillColor= color;
        m_textBorderColor = color.lighter();
    }
    
    
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        QPainter painter(this);
        //fill
        painter.setPen(m_barFillColor);
        painter.setBrush(QBrush(m_barFillColor, Qt::LinearGradientPattern));
        painter.drawRect(2, 10, m_value * width() / m_maxValue - 2, height() - 10 - 2);
        //border
        painter.setPen(m_barBorderColor);
        painter.drawRect(0, 10, width(), height() - 10);
        //caption
        if(m_captionText.isEmpty())
            return;
        painter.setFont(m_font);
        painter.setPen(m_textBorderColor);
        painter.drawText(2, 2, m_captionText);
        QFont font = painter.font();
        font.setWeight(50);
        painter.setFont(font);
        painter.setPen(m_textFillColor);
        painter.drawText(2, 2, m_captionText);
    }
    
private:
    
    
    QFont m_font = QFont("Arial", 8, 80, true);
    QString m_captionText = "Empty bar";
    QColor m_barBorderColor = Qt::black;
    QColor m_barFillColor = Qt::blue;
    QColor m_textBorderColor = Qt::black;
    QColor m_textFillColor = Qt::yellow;
    
    int m_maxValue = 1000;
    int m_value = 0;
    
};

#endif // GMUIINDICATORBAR_H
