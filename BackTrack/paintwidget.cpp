#include <QDebug>
#include <QPen>
#include <QApplication>
#include <QDir>
#include <QPalette>
#include <QPixmap>
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

void PaintWidget::SetBackground()
{
    QString path = QApplication::applicationDirPath();
    QDir dir(path);
    dir.cdUp(); dir.cdUp(); //向上返回两级目录到达工程根目录
    QString projectPath = dir.path();
    QString picturePath = projectPath + "/test1.jpg";
    qDebug() << "picturePath:" << picturePath;

    QPalette palette;
    QImage imgBackground(picturePath);
    QImage fitImg = imgBackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    palette.setBrush(QPalette::Window, QBrush(fitImg));
    this->setPalette(palette);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    paintProcess();
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

    QPainter painter(this);
    QPen pen;
    pen.setStyle(Qt::PenStyle::DashLine);
    pen.setWidth(3);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    float tempProportion = 500;
    int indexLeft;
    for (indexLeft = 0; indexLeft < this->vectorLeft.size() - 1; indexLeft++) {
        if (indexLeft < this->vectorLeft.size() / 6) {
            pen.setColor(Qt::red);
        } else if (indexLeft <= this->vectorLeft.size() / 3 &&
                    indexLeft >= this->vectorLeft.size() / 6) {
            pen.setColor(Qt::yellow);
        } else {
            pen.setColor(Qt::blue);
        }
        painter.setPen(pen);

        float xValueStart = this->vectorLeft[indexLeft].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueStart = this->vectorLeft[indexLeft].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        qDebug() << "(" << xValueStart << ", " << yValueStart << ")";

        float xValueEnd = this->vectorLeft[indexLeft + 1].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueEnd = this->vectorLeft[indexLeft + 1].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        qDebug() << "(" << xValueEnd << ", " << yValueEnd << ")";

        BackLineF backline;
        backline.startPointF = QPointF(xValueStart, yValueStart);
        backline.endPointF = QPointF(xValueEnd, yValueEnd);

        painter.drawLine(backline.startPointF, backline.endPointF);
    }

    int indexRight;
    for (indexRight = 0; indexRight < this->vectorRight.size() - 1; indexRight++) {
        if (indexRight < this->vectorRight.size() / 6) {
            pen.setColor(Qt::red);
        } else if (indexRight <= this->vectorRight.size() / 3 &&
                    indexRight >= this->vectorRight.size() / 6) {
            pen.setColor(Qt::yellow);
        } else {
            pen.setColor(Qt::blue);
        }
        painter.setPen(pen);

        float xValueStart = this->vectorRight[indexRight].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueStart = this->vectorRight[indexRight].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        float xValueEnd = this->vectorRight[indexRight + 1].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
        float yValueEnd = this->vectorRight[indexRight + 1].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

        BackLineF backline;
        backline.startPointF = QPointF(xValueStart, yValueStart);
        backline.endPointF = QPointF(xValueEnd, yValueEnd);

        painter.drawLine(backline.startPointF, backline.endPointF);
    }

    float xValueStart = this->vectorLeft[indexLeft].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
    float yValueStart = this->vectorLeft[indexLeft].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

    float xValueEnd = this->vectorRight[indexRight].x() * tempProportion + PAINT_WIN_WIGHT / 2.0;
    float yValueEnd = this->vectorRight[indexRight].y() * (-1) * tempProportion + PAINT_WIN_HEIGHT;

    BackLineF backline;
    backline.startPointF = QPointF(xValueStart, yValueStart);
    backline.endPointF = QPointF(xValueEnd, yValueEnd);

    painter.drawLine(backline.startPointF, backline.endPointF);

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
    forwardAngle = ((float) percent) / 100.0f * WHEEL_DEGREES_ALPHA;
    qDebug() << "ForwardAngle:" << forwardAngle;
    mode = FORWARD;
    this->update();
}

void PaintWidget::slotBackForwardAngleChanged(int percent)
{
    qDebug() << "BackForwardAngle Percent:" << percent;
    backForwardAngle = ((float) percent) / 100.0f * WHEEL_DEGREES_ALPHA;
    qDebug() << "BackForwardAngle:" << backForwardAngle;
    mode = BACK_FORWARD;
    this->update();
}
