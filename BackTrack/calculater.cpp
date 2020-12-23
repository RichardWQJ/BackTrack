#include <qmath.h>
#include "calculater.h"
#include <QDebug>

Calculater::Calculater()
{
    InitYRealVectorInfo();
}

Calculater::~Calculater()
{

}

void Calculater::InitRealVectorInfo()
{
    InitYRealVectorInfo();
    for (int index = 0; index < SAMPLE_POINT_NUM; index++) {
        QPointF pointLeft(0.9f * (-1), 0.1f * index);
        vecPointRealLeft.push_back(pointLeft);

        QPointF pointRight(0.9f, 0.1f * index);
        vecPointRealRight.push_back(pointRight);
    }
}

void Calculater::CalculateScreenLeftPoints(float angle)
{

}

void Calculater::CalculateScreenRightPoints(float angle)
{

}

void Calculater::InitYRealVectorInfo()
{
#if 0
    for (int index = 1; index <= SAMPLE_POINT_NUM; index++) {
        vecSampleYValue.push_back(0.15f * index);

        QPointF pointInit(0.0f, 0.0f);
        vecScreenLeftPoint.push_back(pointInit);
        vecScreenRightPoint.push_back(pointInit);
    }
#endif

#if 1
    // 地面关键点位置的Y坐标..要考虑到camera能看到的地面的Y的最小值（边界问题）
    vecSampleYValue.push_back(1.25f);
    vecSampleYValue.push_back(1.50f);
    vecSampleYValue.push_back(1.75f);
    vecSampleYValue.push_back(2.00f);
    vecSampleYValue.push_back(2.25f);
    vecSampleYValue.push_back(2.50f);
    vecSampleYValue.push_back(2.75f);
    vecSampleYValue.push_back(3.00f);
    vecSampleYValue.push_back(3.25f);
    vecSampleYValue.push_back(3.50f);
    vecSampleYValue.push_back(3.75f);
    vecSampleYValue.push_back(4.00f);

    vecScreenYValue.push_back(0.05);
    vecScreenYValue.push_back(0.10);
    vecScreenYValue.push_back(0.15);
    vecScreenYValue.push_back(0.20);
    vecScreenYValue.push_back(0.25);
    vecScreenYValue.push_back(0.30);
    vecScreenYValue.push_back(0.35);
    vecScreenYValue.push_back(0.40);
    vecScreenYValue.push_back(0.45);
    vecScreenYValue.push_back(0.50);
    vecScreenYValue.push_back(0.55);
    vecScreenYValue.push_back(0.60);

    for (int index = 1; index <= SAMPLE_POINT_NUM; index++) {
        QPointF pointInit(0.0f, 0.0f);
        vecScreenLeftPoint.push_back(pointInit);
        vecScreenRightPoint.push_back(pointInit);
    }
#endif
}

void Calculater::ComputeScreenPointsWhenForward(float angle)
{
    for (int index = 0; index < SAMPLE_POINT_NUM; index++) {
        float yScrean = vecScreenYValue[index]; //ComputerYr(vecSampleYValue[index]);
        float xLeft = ComputerXr_In(angle, vecSampleYValue[index]) * m_Quotiety;
        QPointF pointLeft(xLeft, yScrean);
        qDebug() << "Left: (" << xLeft << ", " << yScrean << ")";
//        if (isnan(xLeft)) {
//            qDebug() << "xLeft is nan! ";
//            qDebug() << "angle: " << angle << ", vecSampleYValue[index]:" << vecSampleYValue[index];
//        }

        vecScreenLeftPoint[index] = pointLeft;
        float xRight = ComputerXr_Out(angle, vecSampleYValue[index]) * m_Quotiety;
        QPointF pointRight(xRight, yScrean);
        qDebug() << "Right: (" << xRight << ", " << yScrean << ")";
//        if (isnan(xRight)) {
//            qDebug() << "xRight is nan! ";
//            qDebug() << "angle: " << angle << ", vecSampleYValue[index]:" << vecSampleYValue[index];
//        }

        vecScreenRightPoint[index] = pointRight;
    }
}

void Calculater::ComputeScreenPointsWhenBackForward(float angle)
{
    for (int index = 0; index < SAMPLE_POINT_NUM; index++) {
        float yScrean = vecScreenYValue[index]; //ComputerYr(vecSampleYValue[index]);
        float xLeft = ComputerXr_In(angle, vecSampleYValue[index]) * (-1) * m_Quotiety;
        QPointF pointLeft(xLeft, yScrean);
        qDebug() << "Left: (" << xLeft << ", " << yScrean << ")";
//        if (isnan(xLeft)) {
//            qDebug() << "xLeft is nan! ";
//            qDebug() << "angle: " << angle << ", vecSampleYValue[index]:" << vecSampleYValue[index];
//        }

        vecScreenLeftPoint[index] = pointLeft;

        float xRight = ComputerXr_Out(angle, vecSampleYValue[index]) * (-1) * m_Quotiety;
        QPointF pointRight(xRight, yScrean);
        qDebug() << "Right: (" << xRight << ", " << yScrean << ")";
//        if (isnan(xRight)) {
//            qDebug() << "xRight is nan! ";
//            qDebug() << "angle: " << angle << ", vecSampleYValue[index]:" << vecSampleYValue[index];
//        }

        vecScreenRightPoint[index] = pointRight;
    }
}

float Calculater::Cot(float degrees) //参数：角度
{
    float tan = qTan(qDegreesToRadians(degrees)); //角度转弧度
    float cot = 1 / tan;
//    qDebug() << "Cot[" << degrees << "]: " << cot;
    return cot;
}

float Calculater::Square(float number)
{
    return qPow(number, 2);
}

float Calculater::Tan(float degrees) //参数：角度
{
    float tan = qTan(qDegreesToRadians(degrees)); //角度转弧度
    return tan;
}

float Calculater::Sin(float degrees)
{
    float sin = qSin(qDegreesToRadians(degrees));
    return sin;
}

float Calculater::Cos(float degrees)
{
    float cos = qCos(qDegreesToRadians(degrees));
    return cos;
}

float Calculater::ArcTan(float radians) //参数：角度
{
    float arcTan = qAtan(radians);
    return arcTan;
}

float Calculater::ComputerXr_Out(float angle, float y) {
    // L, D, w 已知，
    float firstStep = Square(mL * Cot(angle) + m_w / 2) - Square(y + mD); //外侧后轮
    float secondStep = (float) qPow(firstStep, 0.5f);
    float x = secondStep - mL * Cot(angle);

//    return (float) ((x * cameraWidth) / ((qPow((Square(y) + Square(m_h)), 0.5f) * Tan(mA) * 2))); //小文21的方法
    return (float) ((x * cameraWidth) / (y * Tan(mA) * 2)); //最初的方法
}

float Calculater::ComputerXr_In(float angle, float y) { // 1, 3
    // L, D, w 已知，
    float firstStep = Square(mL * Cot(angle) - m_w / 2) - Square(y + mD); //内侧后轮 -10.8151

    float secondStep = (float) qPow(firstStep, 0.5f);
    float x = secondStep - mL * Cot(angle);

//    return (float) ((x * cameraWidth) / ((qPow((Square(y) + Square(m_h)), 0.5f) * Tan(mA) * 2))); //小文21的方法
    return (float) ((x * cameraWidth) / (y * Tan(mA) * 2)); //最初的方法
}

float Calculater::ComputerYr(float y)
{
    // L, D, W 已知
    float firstStep = Sin(mA + mB - ArcTan(m_h / y)) / Cos(mB - ArcTan(m_h / y));
    float secondStep = cameraHeight / (2 * Sin(mA));
    return (float) firstStep * secondStep;
}
