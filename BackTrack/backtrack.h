#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDialog>
#include <QPushButton>
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
    void InitConfigDialog();
    void DataInitBeforeDialgDisplay();
    void DataSaveAfterClickSaveBtn();

signals:
public slots:
    void slotForwardAngleChanged(int percent);
    void slotBackForwardAngleChanged(int percent);
    void slotConfigDialogShow();
    void slotMainWindowShow();
    void slotSaveConfigData();

private:
    Ui::BackTrack *ui;

    QMenuBar* pMenuBar; // 菜单栏
    QMenu* pMenuA;

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

    /******************************/
    QDialog *configDialog;

    QLabel *lableConfig_mD; // 车尾到车后轮的距离D
    QDoubleSpinBox *spinboxConfig_mD;

    QLabel *lableConfig_mL; // 车前后轮的轴距L
    QDoubleSpinBox *spinboxConfig_mL;

    QLabel *lableConfig_mw; // 车的轴长w
    QDoubleSpinBox *spinboxConfig_mw;

    QLabel *lableConfig_mh; // camera的高度h
    QDoubleSpinBox *spinboxConfig_mh;

    QLabel *lableConfig_mB; // 摄像头中心线同水平面的夹角β
    QSpinBox *spinboxConfig_mB;

    QLabel *lableConfig_mA; // α, 当α越大，两条线越靠近，变化趋势相对平缓；α越小，两条线越远离，变化趋势相对剧烈
    QSpinBox *spinboxConfig_mA;

    QLabel *lableConfigCameraW; // 屏幕的宽度W
    QDoubleSpinBox *spinboxConfigCameraW;

    QLabel *lableConfigCameraH; // 屏幕的高度H
    QDoubleSpinBox *spinboxConfigCameraH;

    QPushButton *btnCancle;
    QPushButton *btnSave;
    /******************************/
};

#endif // BACKTRACK_H
