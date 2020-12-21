#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include "paintwidget.h"

#define MAIN_WIDGET_WIDTH   500
#define MAIN_WIDGET_HEIGTH  700

#define SLIDER_MIN_VALUE    1
#define SLIDER_MAX_VALUE    100
#define SLIDER_STEP_VALUE   1

namespace Ui {
class BackTrack;
}

class BackTrack : public QMainWindow
{
    Q_OBJECT

public:
    explicit BackTrack(QWidget *parent = 0);
    ~BackTrack();

    void LoadStyleSheet();
    void InitWidget();

signals:
public slots:
    void slotForwardAngleChanged(int percent);
    void slotBackForwardAngleChanged(int percent);

private:
    Ui::BackTrack *ui;
    // 顺时针滑动条标签
    QLabel *lableSliderForward;

    // 逆时针滑动条标签
    QLabel *lableSliderBackForward;

    // 顺时针滑动条
    QSlider *pSliderForward;

    // 逆时针滑动条
    QSlider *pSliderBackForward;

    // 当前顺时针角度标签
    QLabel *angleSliderForward;

    // 当前逆时针角度标签
    QLabel *angleSliderBackForward;

    // 顺时针当前角度
    QLabel *currAngleForward;

    // 逆时针当前角度
    QLabel *currAngleBackForward;

    PaintWidget *paintWidget;
};

#endif // BACKTRACK_H
