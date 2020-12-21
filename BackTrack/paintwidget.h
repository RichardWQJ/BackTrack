#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include "calculater.h"

enum CURRENT_MODE {
    FORWARD,
    BACK_FORWARD
};

// 长宽和标题
#define PAINT_WIN_WIGHT     500
#define PAINT_WIN_HEIGHT    500

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = 0);
signals:

public slots:
    void slotForwardAngleChanged(int percent);
    void slotBackForwardAngleChanged(int percent);

protected:
    void paintEvent(QPaintEvent *event);
    void paintProcess();
    void drawTrack();
    void drawForwardTrack();
    void drawBackForwardTrack();

private:
    QPixmap pix;
    float forwardAngle;
    float backForwardAngle;
    CURRENT_MODE mode;
    int widgetWidth;
    int widgetHeight;
    Calculater calculater;

    QVector<QPointF> vectorLeft;
    QVector<QPointF> vectorRight;
};

#endif // PAINTWIDGET_H
