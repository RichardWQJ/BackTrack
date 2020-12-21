#ifndef CALCULATER_H
#define CALCULATER_H

#include <QPoint>
#include <QPointF>
#include <QVector>

#define SAMPLE_REAL_WIDTH   180
#define SAMPLE_REAL_HEIGTH  300
#define SAMPLE_POINT_NUM    12  //(SAMPLE_REAL_HEIGTH / 10)

typedef struct myLine {
    QPoint startPoint;
    QPoint endPoint;
} BackLine;

typedef struct myLineF {
    QPointF startPointF;
    QPointF endPointF;
} BackLineF;

class Calculater
{
public:
    /******************************************************/
    float mAngle = 0; // 转角φ
    float mD = 0.5f;  // 车尾到车后轮的距离D
    float mL = 2.8f;  // 车前后轮的轴距L
    float m_w = 1.2f;  // 车的轴长w
    float m_h = 1.5f;  // camera的高度h
    float mB = 10;    // 摄像头中心线同水平面的夹角β
    float mA = 30;    // 当α越大，两条线越靠近，变化趋势相对平缓；α越小，两条线越远离，变化趋势相对剧烈
    float cameraWidth = 0.8f;  // 屏幕的宽度W
    float cameraHeight = 0.6f;  // 屏幕的高度H
    /******************************************************/

    /***********************拟用的方法***********************/

    QVector<QPointF> vecPointRealLeft;
    QVector<QPointF> vecPointRealRight;

    QVector<QPointF> vecPointScreenLeft;
    QVector<QPointF> vecPointScreenRight;

    void InitRealVectorInfo();

    void CalculateScreenLeftPoints(float angle);

    void CalculateScreenRightPoints(float angle);

    /***********************小文21的方法**********************/

    QVector<float> vecSampleYValue;
    QVector<float> vecScreenYValue;

    QVector<QPointF> vecScreenLeftPoint;
    QVector<QPointF> vecScreenRightPoint;

    void InitYRealVectorInfo();

    void ComputeScreenPointsWhenForward(float angle);

    void ComputeScreenPointsWhenBackForward(float angle);

    /*******************************************************/

    float ComputerXr_Out(float angle, float y);

    float ComputerXr_In(float angle, float y);

    float ComputerYr(float y);

    /******************************************************/

private:
    /* 地面关键点位置的X坐标 */
    float mArrayX[24] = {10, 10, 10, 10, 10, 10, 10, 10,
                         10, 10, 10, 10, 10, 10, 10, 10,
                         10, 10, 10, 10, 10, 10, 10, 10};

    /* 地面关键点位置的Y坐标..要考虑到camera能看到的地面的Y的最小值（边界问题）*/
    float mArrayY[24] = {4, 3.75f, 3.5f, 3.25f, 3, 2.75f, 2.5f, 2.25f, 2, 1.75f, 1.5f, 1.25f,
                         1.25f, 1.5f, 1.75f, 2, 2.25f, 2.5f, 2.75f, 3, 3.25f, 3.5f, 3.75f, 4};

    /* 保存屏幕上Y轴的坐标Yr */
    float mArrayYR[24] = {0.6f, 0.55f, 0.5f, 0.45f, 0.4f, 0.35f, 0.3f, 0.25f, 0.2f, 0.15f, 0.1f, 0.05f,
                          0.05f, 0.1f, 0.15f, 0.2f, 0.25f, 0.3f, 0.35f, 0.4f, 0.45f, 0.5f, 0.55f, 0.6f};

    /* 顶点数组 */
    float mArray[52 * 3] = {
        mArrayX[0], mArrayYR[0] * 2 - 1, 0,
        mArrayX[1], mArrayYR[1] * 2 - 1, 0,

        mArrayX[1], mArrayYR[1] * 2 - 1, 0,
        mArrayX[2], mArrayYR[2] * 2 - 1, 0,

        mArrayX[2], mArrayYR[2] * 2 - 1, 0,
        mArrayX[3], mArrayYR[3] * 2 - 1, 0,

        mArrayX[3], mArrayYR[3] * 2 - 1, 0,
        mArrayX[4], mArrayYR[4] * 2 - 1, 0,

        mArrayX[4], mArrayYR[4] * 2 - 1, 0,
        mArrayX[5], mArrayYR[5] * 2 - 1, 0,

        mArrayX[5], mArrayYR[5] * 2 - 1, 0,
        mArrayX[6], mArrayYR[6] * 2 - 1, 0,

        mArrayX[6], mArrayYR[6] * 2 - 1, 0,
        mArrayX[7], mArrayYR[7] * 2 - 1, 0,

        mArrayX[7], mArrayYR[7] * 2 - 1, 0,
        mArrayX[8], mArrayYR[8] * 2 - 1, 0,

        mArrayX[8], mArrayYR[8] * 2 - 1, 0,
        mArrayX[9], mArrayYR[9] * 2 - 1, 0,

        mArrayX[9], mArrayYR[9] * 2 - 1, 0,
        mArrayX[10], mArrayYR[10] * 2 - 1, 0,

        mArrayX[10], mArrayYR[10] * 2 - 1, 0,
        mArrayX[11], mArrayYR[11] * 2 - 1, 0,


        mArrayX[12], mArrayYR[12] * 2 - 1, 0,
        mArrayX[13], mArrayYR[13] * 2 - 1, 0,

        mArrayX[13], mArrayYR[13] * 2 - 1, 0,
        mArrayX[14], mArrayYR[14] * 2 - 1, 0,

        mArrayX[14], mArrayYR[14] * 2 - 1, 0,
        mArrayX[15], mArrayYR[15] * 2 - 1, 0,

        mArrayX[15], mArrayYR[15] * 2 - 1, 0,
        mArrayX[16], mArrayYR[16] * 2 - 1, 0,

        mArrayX[16], mArrayYR[16] * 2 - 1, 0,
        mArrayX[17], mArrayYR[17] * 2 - 1, 0,

        mArrayX[17], mArrayYR[17] * 2 - 1, 0,
        mArrayX[18], mArrayYR[18] * 2 - 1, 0,

        mArrayX[18], mArrayYR[18] * 2 - 1, 0,
        mArrayX[19], mArrayYR[19] * 2 - 1, 0,

        mArrayX[19], mArrayYR[19] * 2 - 1, 0,
        mArrayX[20], mArrayYR[20] * 2 - 1, 0,

        mArrayX[20], mArrayYR[20] * 2 - 1, 0,
        mArrayX[21], mArrayYR[21] * 2 - 1, 0,

        mArrayX[21], mArrayYR[21] * 2 - 1, 0,
        mArrayX[22], mArrayYR[22] * 2 - 1, 0,

        mArrayX[22], mArrayYR[22] * 2 - 1, 0,
        mArrayX[23], mArrayYR[23] * 2 - 1, 0,

        // 静态区域 (手动配)
        -0.1f, 0.2f, 0,
        -0.2f, -0.9f, 0,  // 左边

        -0.2f, -0.9f, 0,
        0.2f, -0.9f, 0,  // 底边

        0.2f, -0.9f, 0,
        0.1f, 0.2f, 0,  // 右边

        0.1f, 0.2f, 0,
        -0.1f, 0.2f, 0,  // 上边
    };

    /* 求反切值 */
    float Cot(float degrees);

    /* 求平方 */
    float Square(float number);

    /* 求正切值 */
    float Tan(float degrees);

    float Sin(float degrees);

    float Cos(float degrees);

    float ArcTan(float radians);
};


#endif // CALCULATER_H
