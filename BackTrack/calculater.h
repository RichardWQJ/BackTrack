#ifndef CALCULATER_H
#define CALCULATER_H

#include <QPoint>
#include <QPointF>
#include <QVector>
#include "singleton.h"

#define SAMPLE_REAL_WIDTH   180
#define SAMPLE_REAL_HEIGTH  300
#define SAMPLE_POINT_NUM    12 + 8

#define WHEEL_DEGREES_ALPHA 20

typedef struct myLine {
    QPoint startPoint;
    QPoint endPoint;
} BackLine;

typedef struct myLineF {
    QPointF startPointF;
    QPointF endPointF;
} BackLineF;

class Calculater : public Singleton<Calculater>
{
    friend class Singleton<Calculater>;

public:
    inline float Get_mD() { return mD; }
    inline float Get_mL() { return mL; }
    inline float Get_mw() { return m_w; }
    inline float Get_mh() { return m_h; }

    inline float Get_mB() { return mB; }
    inline float Get_mA() { return mA; }

    inline float GetCameraWidth() { return cameraWidth; }
    inline float GetCameraHeight() { return cameraHeight; }
    inline float GetQuotiety() { return m_Quotiety; }

    inline void Set_mD(float D) { mD = D; }
    inline void Set_mL(float L) { mL = L; }
    inline void Set_mw(float w) { m_w = w; }
    inline void Set_mh(float h) { m_h = h; }

    inline void Set_mB(int B) { mB = B; }
    inline void Set_mA(int A) { mA = A; }

    inline void SetCameraWidth(float width) { cameraWidth = width; }
    inline void SetCameraHeight(float height) { cameraHeight = height; }
    inline void SetQuotiety(float quotiety) { m_Quotiety = quotiety; }

    /***********************拟用的方法***********************/
    Calculater();
    ~Calculater();

    QVector<QPointF> vecPointRealLeft;
    QVector<QPointF> vecPointRealRight;

    QVector<QPointF> vecPointScreenLeft;
    QVector<QPointF> vecPointScreenRight;

//    void InitRealVectorInfo();

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

    /* 求反切值 */
    float Cot(float degrees);

    /* 求平方 */
    float Square(float number);

    /* 求正切值 */
    float Tan(float degrees);

    float Sin(float degrees);

    float Cos(float degrees);

    float ArcTan(float radians);

    /******************************************************/
    float mAngle = 0; // 转角φ
    float mD = 0.5f;  // 车尾到车后轮的距离D
    float mL = 2.8f;  // 车前后轮的轴距L
    float m_w = 1.2f;  // 车的轴长w
    float m_h = 1.0f;  // camera的高度h
    float mB = 10;    // 摄像头中心线同水平面的夹角β
    float mA = 30;    // 当α越大，两条线越靠近，变化趋势相对平缓；α越小，两条线越远离，变化趋势相对剧烈
    float cameraWidth = 0.8f;  // 屏幕的宽度W
    float cameraHeight = 1.0f;  // 屏幕的高度H
    /******************************************************/

    float m_Quotiety = 1.0f;
};

#endif // CALCULATER_H
