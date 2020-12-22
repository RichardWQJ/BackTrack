#include "backtrack.h"
#include "ui_backtrack.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QFont>
#include <QAction>
#include "calculater.h"

BackTrack::BackTrack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BackTrack)
{
    ui->setupUi(this);
    this->setFixedSize(MAIN_WIDGET_WIDTH, MAIN_WIDGET_HEIGTH);
    LoadStyleSheet();
    InitWidget();
    InitConfigDialog();
}

BackTrack::~BackTrack()
{
    delete ui;
}

void BackTrack::LoadStyleSheet()
{
    //加载皮肤
#if 1
    QString path = QApplication::applicationDirPath();
    qDebug() << "CurrentPath: " << path;

    QDir dir(path);

    dir.cdUp(); dir.cdUp(); //向上返回两级目录到达工程根目录
    QString projectPath = dir.path();
    qDebug() << "projectPath: " << projectPath;

    QFile file(projectPath + "/stylesheet.qss");
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Warning"), tr("Faild to open file!!!"), QMessageBox::Ok);
        return;
    }
    QString styleSheet = QLatin1String(file.readAll());
    file.close();

    this->setStyleSheet(styleSheet);
#endif
}

void BackTrack::InitWidget()
{
    pMenuBar = this->ui->menuBar;
    pMenuA = new QMenu("配置");    // q则为Alt方式的快捷键

    // 新建一个Action，然后加入到菜单A中
    QAction* pActionA = new QAction("参数配置");
    pMenuA->addAction(pActionA);

    //　将菜单A再添加到MenuBar中
    pMenuBar->addMenu(pMenuA);

    // 顺时针滑动条标签
    this->lableSliderForward = new QLabel(tr("        顺时针："));
    this->lableSliderForward->setParent(this);
    this->lableSliderForward->setFixedSize(100, 40);

    // 逆时针滑动条标签
    this->lableSliderBackForward = new QLabel(tr("        逆时针："));
    this->lableSliderBackForward->setParent(this);
    this->lableSliderBackForward->setFixedSize(100, 40);

    // 顺时针滑动条
    this->pSliderForward = new QSlider(this);
    this->pSliderForward->setOrientation(Qt::Horizontal);  // 水平方向
    this->pSliderForward->setMinimum(SLIDER_MIN_VALUE);  // 最小值
    this->pSliderForward->setMaximum(SLIDER_MAX_VALUE);  // 最大值
    this->pSliderForward->setSingleStep(SLIDER_STEP_VALUE);  // 步长
    this->pSliderForward->setFixedSize(250, 40);

    // 逆时针滑动条
    this->pSliderBackForward = new QSlider(this);
    this->pSliderBackForward->setOrientation(Qt::Horizontal);  // 水平方向
    this->pSliderBackForward->setMinimum(SLIDER_MIN_VALUE);  // 最小值
    this->pSliderBackForward->setMaximum(SLIDER_MAX_VALUE);  // 最大值
    this->pSliderBackForward->setSingleStep(SLIDER_STEP_VALUE);  // 步长
    this->pSliderBackForward->setFixedSize(250, 40);

    // 当前顺时针角度标签
    this->angleSliderForward = new QLabel(tr("顺时针当前角度："));
    this->angleSliderForward->setParent(this);
    this->angleSliderForward->setFixedSize(100, 40);

    // 当前逆时针角度标签
    this->angleSliderBackForward = new QLabel(tr("逆时针当前角度："));
    this->angleSliderBackForward->setParent(this);
    this->angleSliderBackForward->setFixedSize(100, 40);

    // 顺时针当前角度
    this->currAngleForward = new QLabel(this);
    this->currAngleForward->clear();
    this->currAngleForward->setFixedSize(100, 40);

    // 逆时针当前角度
    this->currAngleBackForward = new QLabel(this);
    this->currAngleBackForward->clear();
    this->currAngleBackForward->setFixedSize(100, 40);

    this->paintWidget = new PaintWidget(this);
    this->paintWidget->setBackgroundRole(QPalette::Dark);

    QGridLayout *mainLayout1 = new QGridLayout(this);
    mainLayout1->addWidget(lableSliderForward, 0, 0);
    mainLayout1->addWidget(pSliderForward, 0, 1);
    mainLayout1->addWidget(lableSliderBackForward, 1, 0);
    mainLayout1->addWidget(pSliderBackForward, 1, 1);

    mainLayout1->addWidget(angleSliderForward, 2, 0);
    mainLayout1->addWidget(currAngleForward, 2, 1);
    mainLayout1->addWidget(angleSliderBackForward, 3, 0);
    mainLayout1->addWidget(currAngleBackForward, 3, 1);

    mainLayout1->setRowMinimumHeight(0, 20);
    mainLayout1->setRowMinimumHeight(1, 20);
    mainLayout1->setColumnMinimumWidth(0, 20);
    mainLayout1->setColumnMinimumWidth(1, 20);

    QHBoxLayout *mainLayout2 = new QHBoxLayout;
    mainLayout2->setMargin(10);
    mainLayout2->addStretch();
    mainLayout2->addWidget(paintWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(mainLayout1);
    mainLayout->addLayout(mainLayout2);

    this->centralWidget()->setLayout(mainLayout); //重点!!!

    // 连接信号槽（相互改变）
    connect(this->pSliderForward, SIGNAL(valueChanged(int)), this, SLOT(slotForwardAngleChanged(int)));
    connect(this->pSliderBackForward, SIGNAL(valueChanged(int)), this, SLOT(slotBackForwardAngleChanged(int)));

    connect(this->pSliderForward, SIGNAL(valueChanged(int)), paintWidget, SLOT(slotForwardAngleChanged(int)));
    connect(this->pSliderBackForward, SIGNAL(valueChanged(int)), paintWidget, SLOT(slotBackForwardAngleChanged(int)));

    connect(pActionA, SIGNAL(triggered(bool)), this, SLOT(slotConfigDialogShow()));
}

void BackTrack::InitConfigDialog()
{
    configDialog = new QDialog(this);

    lableConfig_mD = new QLabel(tr("车尾到车后轮的距离D:"));
    spinboxConfig_mD = new QDoubleSpinBox();
    spinboxConfig_mD->setRange(0.4, 0.8);
    spinboxConfig_mD->setSingleStep(0.1);

    lableConfig_mL = new QLabel(tr("车前后轮的轴距L:"));
    spinboxConfig_mL = new QDoubleSpinBox();
    spinboxConfig_mL->setRange(2.4, 3.2);
    spinboxConfig_mL->setSingleStep(0.1);

    lableConfig_mw = new QLabel(tr("车的轴长w:"));
    spinboxConfig_mw = new QDoubleSpinBox();
    spinboxConfig_mw->setRange(1.0, 1.8);
    spinboxConfig_mw->setSingleStep(0.1);

    lableConfig_mh = new QLabel(tr("camera的高度h:"));
    spinboxConfig_mh = new QDoubleSpinBox();
    spinboxConfig_mh->setRange(1.0, 2.0);
    spinboxConfig_mh->setSingleStep(0.1);

    lableConfig_mB = new QLabel(tr("摄像头中心线同水平面的夹角B:"));
    spinboxConfig_mB = new QSpinBox();
    spinboxConfig_mB->setRange(8, 16);
    spinboxConfig_mB->setSingleStep(1);

    lableConfig_mA = new QLabel(tr("摄像头张角的一半a:"));
    spinboxConfig_mA = new QSpinBox();
    spinboxConfig_mA->setRange(20, 60);
    spinboxConfig_mA->setSingleStep(1);

    lableConfigCameraW = new QLabel(tr("屏幕的宽度W:"));
    spinboxConfigCameraW = new QDoubleSpinBox();
    spinboxConfigCameraW->setRange(0.4, 1.2);
    spinboxConfigCameraW->setSingleStep(0.1);

    lableConfigCameraH = new QLabel(tr("屏幕的高度H:"));
    spinboxConfigCameraH = new QDoubleSpinBox();
    spinboxConfigCameraH->setRange(0.4, 1.0);
    spinboxConfigCameraH->setSingleStep(0.1);

    btnCancle = new QPushButton(tr("取消"));
    btnSave = new QPushButton(tr("保存"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lableConfig_mD, 1, 1);
    mainLayout->addWidget(spinboxConfig_mD, 1, 2);

    mainLayout->addWidget(lableConfig_mL, 2, 1);
    mainLayout->addWidget(spinboxConfig_mL, 2, 2);

    mainLayout->addWidget(lableConfig_mw, 3, 1);
    mainLayout->addWidget(spinboxConfig_mw, 3, 2);

    mainLayout->addWidget(lableConfig_mh, 4, 1);
    mainLayout->addWidget(spinboxConfig_mh, 4, 2);

    mainLayout->addWidget(lableConfig_mB, 5, 1);
    mainLayout->addWidget(spinboxConfig_mB, 5, 2);

    mainLayout->addWidget(lableConfig_mA, 6, 1);
    mainLayout->addWidget(spinboxConfig_mA, 6, 2);

    mainLayout->addWidget(lableConfigCameraW, 7, 1);
    mainLayout->addWidget(spinboxConfigCameraW, 7, 2);

    mainLayout->addWidget(lableConfigCameraH, 8, 1);
    mainLayout->addWidget(spinboxConfigCameraH, 8, 2);

    mainLayout->addWidget(btnSave, 9, 1);
    mainLayout->addWidget(btnCancle, 9, 2);

    configDialog->setLayout(mainLayout);
    configDialog->setFixedSize(250, 350);
    configDialog->setWindowTitle(tr("配置基础信息"));

    connect(this->configDialog, SIGNAL(rejected()), this, SLOT(slotMainWindowShow()));
    connect(this->btnCancle, SIGNAL(clicked(bool)), this->configDialog, SLOT(close()));
    connect(this->btnSave, SIGNAL(clicked(bool)), this, SLOT(slotSaveConfigData()));
}

void BackTrack::DataInitBeforeDialgDisplay()
{
    spinboxConfig_mD->setValue(Calculater::GetInstance()->Get_mD());
    spinboxConfig_mL->setValue(Calculater::GetInstance()->Get_mL());
    spinboxConfig_mw->setValue(Calculater::GetInstance()->Get_mw());
    spinboxConfig_mh->setValue(Calculater::GetInstance()->Get_mh());
    spinboxConfig_mB->setValue(Calculater::GetInstance()->Get_mB());
    spinboxConfig_mA->setValue(Calculater::GetInstance()->Get_mA());
    spinboxConfigCameraW->setValue(Calculater::GetInstance()->GetCameraWidth());
    spinboxConfigCameraH->setValue(Calculater::GetInstance()->GetCameraHeight());
}

void BackTrack::DataSaveAfterClickSaveBtn()
{
    Calculater::GetInstance()->Set_mD(spinboxConfig_mD->value());
    Calculater::GetInstance()->Set_mD(spinboxConfig_mD->value());
}

void BackTrack::slotForwardAngleChanged(int percent)
{
    float angle = percent / 100.0f * 25.0f;
    this->currAngleForward->setText(QString::number(angle));
}

void BackTrack::slotBackForwardAngleChanged(int percent)
{
    float angle = percent / 100.0f * 25.0f;
    this->currAngleBackForward->setText(QString::number(angle));
}

void BackTrack::slotConfigDialogShow()
{
    DataInitBeforeDialgDisplay();
    this->configDialog->show();
    this->hide();
    qDebug() << "Main Window oughted to be hiden!";
}

void BackTrack::slotMainWindowShow()
{
    this->show();
    qDebug() << "Main Window oughted to be show!";
}

void BackTrack::slotSaveConfigData()
{
    qDebug() << "slotSaveConfigData";
    this->configDialog->close();
}
