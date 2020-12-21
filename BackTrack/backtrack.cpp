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

BackTrack::BackTrack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BackTrack)
{
    ui->setupUi(this);
    this->setFixedSize(MAIN_WIDGET_WIDTH, MAIN_WIDGET_HEIGTH);
    LoadStyleSheet();
    InitWidget();
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
    int nMin = 0;
    int nMax = 100;
    int nSingleStep = 1;

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
//    mainLayout->setMargin(10);  //表示控件与窗体的左右边距
//    mainLayout->setSpacing(5); //表示各个控件之间的上下间距
    mainLayout->addLayout(mainLayout1);
    mainLayout->addLayout(mainLayout2);

    this->centralWidget()->setLayout(mainLayout); //重点!!!

    // 连接信号槽（相互改变）
    connect(this->pSliderForward, SIGNAL(valueChanged(int)), this, SLOT(slotForwardAngleChanged(int)));
    connect(this->pSliderBackForward, SIGNAL(valueChanged(int)), this, SLOT(slotBackForwardAngleChanged(int)));

    connect(this->pSliderForward, SIGNAL(valueChanged(int)), paintWidget, SLOT(slotForwardAngleChanged(int)));
    connect(this->pSliderBackForward, SIGNAL(valueChanged(int)), paintWidget, SLOT(slotBackForwardAngleChanged(int)));
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

