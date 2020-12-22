#include <QDebug>
#include <QPen>
#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    /*pix = QPixmap(WIN_WIGHT, WIN_HEIGHT);
    pix.fill(Qt::white);*/

    this->calculater = Calculater::GetInstance();
    this->setFixedSize(PAINT_WIN_WIGHT, PAINT_WIN_HEIGHT);
    this->widgetWidth = this->geometry().width();
    this->widgetHeight = this->geometry().height();

    qDebug() << "Width:" << this->widgetWidth;
    qDebug() << "Height:" << this->widgetHeight;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    paintProcess();
    /*QPainter Painter(this);
    Painter.drawPixmap(0, 0, WIN_WIGHT, WIN_HEIGHT, pix);*/
}

void PaintWidget::paintProcess()
{
    switch (this->mode)
    {
    case FORWARD:
    {
        drawForwardTrack();
    } break;
    case BACK_FORWARD:
    {
        drawBackForwardTrack();
    } break;
    default:
        break;
    }
}

void PaintWidget::drawTrack()
{
    qDebug() << "Draw Start";
    qDebug() << "Left Size:" << vectorLeft.size();
    qDebug() << "Right Size:" << vectorRight.size();

#if 0
    if (this->mode == FORWARD) {
        foreach (QPointF point, this->vectorLeft) {
            qDebug() << "(" << point.x() << ", " << point.y() << ")";

        }
    } else {
        foreach (QPointF point, this->vectorRight) {
            qDebug() << "(" << point.x() << ", " << point.y() << ")";

        }
    }
#endif

#if 1
    QPainter p(this);
    p.setPen(QPen(Qt::red, 3));
    float tempProportion = 500;
    int indexLeft;
    for (indexLeft = 0; indexLeft < this->vectorLeft.size() - 1; indexLeft++) {
        if (indexLeft < this->vectorLeft.size() / 4) {
            p.setPen(QPen(Qt::red, 3));
        } else if (indexLeft <= this->vectorLeft.size() / 2 &&
                    indexLeft >= this->vectorLeft.size() / 4) {
            p.setPen(QPen(Qt::yellow, 3));
        } else {
            p.setPen(QPen(Qt::blue, 3));
        }

        float xValueStart = this->vectorLeft[indexLeft].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueStart = this->vectorLeft[indexLeft].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        qDebug() << "(" << xValueStart << ", " << yValueStart << ")";

        float xValueEnd = this->vectorLeft[indexLeft + 1].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueEnd = this->vectorLeft[indexLeft + 1].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        qDebug() << "(" << xValueEnd << ", " << yValueEnd << ")";

        BackLineF backline;
        backline.startPointF = QPointF(xValueStart, yValueStart);
        backline.endPointF = QPointF(xValueEnd, yValueEnd);

        p.drawLine(backline.startPointF, backline.endPointF);
    }

    int indexRight;
    for (indexRight = 0; indexRight < this->vectorRight.size() - 1; indexRight++) {
        if (indexRight < this->vectorRight.size() / 4) {
            p.setPen(QPen(Qt::red, 3));
        } else if (indexRight <= this->vectorRight.size() / 2 &&
                    indexRight >= this->vectorRight.size() / 4) {
            p.setPen(QPen(Qt::yellow, 3));
        } else {
            p.setPen(QPen(Qt::blue, 3));
        }

        float xValueStart = this->vectorRight[indexRight].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueStart = this->vectorRight[indexRight].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        float xValueEnd = this->vectorRight[indexRight + 1].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueEnd = this->vectorRight[indexRight + 1].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        BackLineF backline;
        backline.startPointF = QPointF(xValueStart, yValueStart);
        backline.endPointF = QPointF(xValueEnd, yValueEnd);

        p.drawLine(backline.startPointF, backline.endPointF);
    }

    float xValueStart = this->vectorLeft[indexLeft].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
    float yValueStart = this->vectorLeft[indexLeft].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

    float xValueEnd = this->vectorRight[indexRight].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
    float yValueEnd = this->vectorRight[indexRight].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

    BackLineF backline;
    backline.startPointF = QPointF(xValueStart, yValueStart);
    backline.endPointF = QPointF(xValueEnd, yValueEnd);

    p.drawLine(backline.startPointF, backline.endPointF);
#endif
    qDebug() << "Draw End";
}

void PaintWidget::drawForwardTrack()
{
    calculater->ComputeScreenPointsWhenForward(this->forwardAngle);
    vectorLeft = calculater->vecScreenLeftPoint;
    vectorRight = calculater->vecScreenRightPoint;
    drawTrack();
}

void PaintWidget::drawBackForwardTrack()
{
    calculater->ComputeScreenPointsWhenBackForward(this->backForwardAngle);
    vectorLeft = calculater->vecScreenLeftPoint;
    vectorRight = calculater->vecScreenRightPoint;
    drawTrack();
}

void PaintWidget::slotForwardAngleChanged(int percent)
{
    qDebug() << "ForwardAngle Percent:" << percent;
    forwardAngle = ((float) percent) / 100.0f * 25.0f;
    qDebug() << "ForwardAngle:" << forwardAngle;
    mode = FORWARD;
    this->update();

    /*BackLine backline;
    backline.startPoint = QPoint(forwardPercent, 0);
    backline.endPoint = QPoint(0, forwardPercent);

    QPainter p(&this->pix);
    p.setPen(Qt::red);
    p.drawLine(backline.startPoint, backline.endPoint);*/
}

void PaintWidget::slotBackForwardAngleChanged(int percent)
{
    qDebug() << "BackForwardAngle Percent:" << percent;
    backForwardAngle = ((float) percent) / 100.0f * 25.0f;
    qDebug() << "BackForwardAngle:" << backForwardAngle;
    mode = BACK_FORWARD;
    this->update();

    /*BackLine backline;
    backline.startPoint = QPoint(backForwardPercent, 0);
    backline.endPoint = QPoint(0, backForwardPercent);

    QPainter p(&this->pix);
    p.setPen(Qt::blue);
    p.drawLine(backline.startPoint, backline.endPoint);*/
}
