#include "musicplaywidget.h"
#include "qpushbutton.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#define MUSICPLAYWIDGET_WIDTH 480
#define MUSICPLAYWIDGET_HEIGHT 756

#define MUSICPLAYBUTTONWIDGET_WIDTH 80
#define MUSICPLAYBUTTONWIDGET_HEIGHT 80

#define CDJOYSTICK_POS_X 440
#define CDJOYSTICK_POS_Y 144

MusicPlayWidget::MusicPlayWidget(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(0,100,MUSICPLAYWIDGET_WIDTH,MUSICPLAYWIDGET_HEIGHT);
    loadWidgetButton();
    loadSliders();

    float rotateRad = m_joyStickRotAngle*MATH_PI/180;
    float posAX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthA;
    float posAY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthA;

    float posBX = CDJOYSTICK_POS_X - sin(m_angleBOrg+rotateRad)*m_lengthB;
    float posBY = CDJOYSTICK_POS_Y + cos(m_angleBOrg+rotateRad)*m_lengthB;

    float posCX = CDJOYSTICK_POS_X - sin(m_angleCOrg+rotateRad)*m_lengthC;
    float posCY = CDJOYSTICK_POS_Y + cos(m_angleCOrg+rotateRad)*m_lengthC;

    float posDX = CDJOYSTICK_POS_X - sin(m_angleDOrg+rotateRad)*m_lengthD;
    float posDY = CDJOYSTICK_POS_Y + cos(m_angleDOrg+rotateRad)*m_lengthD;

    m_posAOrg = Vec2f(posAX,posAY);
    m_posBOrg = Vec2f(posBX,posBY);
    m_posCOrg = Vec2f(posCX,posCY);
    m_posDOrg = Vec2f(posDX,posDY);

    m_posACur = m_posAOrg;
    m_posBCur = m_posBOrg;
    m_posCCur = m_posCOrg;
    m_posDCur = m_posDOrg;

    qDebug()<<"PosA::"<< m_posACur.x<<" "<<m_posACur.y;
    qDebug()<<"PosB::"<< m_posBCur.x<<" "<<m_posBCur.y;
    qDebug()<<"PosC::"<< m_posCCur.x<<" "<<m_posCCur.y;
    qDebug()<<"PosD::"<< m_posDCur.x<<" "<<m_posDCur.y;
}

void MusicPlayWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.save();
    painter.translate(width()/2,326);
    painter.rotate(m_cdRotateAngle);
    painter.drawPixmap(QRect(-211,-211,422,422),QPixmap(":/images/Resources/cdBackground.png"));
    painter.restore();

    painter.save();
    painter.translate(CDJOYSTICK_POS_X,CDJOYSTICK_POS_Y);
    painter.rotate(m_joyStickRotAngle);
    painter.drawPixmap(QRect(-123,-48,211,417),QPixmap(":/images/Resources/cdPlayJoystick.png"));
    painter.restore();

}

void MusicPlayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton))
        return;
    const QPoint currPos = event->pos();
    const QPoint diffPos = currPos - m_lastMousePos;

    if(diffPos.isNull())
        return;
    //如果鼠标在有效区域内
    if(m_bMouseInJoyStickRect)
    {
        m_mouseMoveAngle = caculateMouseMoveAngle(currPos);
        float t_rotateAngle = m_mouseLastAngle + m_mouseMoveAngle;

        t_rotateAngle = qBound(0.0f,t_rotateAngle,22.0f);
        m_joyStickRotAngle = t_rotateAngle;
        update();
    }
}

void MusicPlayWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_lastMousePos = event->pos();
        const QPoint currPos = event->pos();
        //判断当前点是否在有效区域
        bool isInRect = judgePointInRect(currPos);

        if(isInRect)
            m_bMouseInJoyStickRect = isInRect;
    }
}

void MusicPlayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_bMouseInJoyStickRect)
    {
        m_mouseLastAngle += m_mouseMoveAngle;
        m_mouseLastAngle = qBound(0.0f,m_mouseLastAngle,22.0f);
        //更新有效区域四个点的位置
        updateCurrentJoyStickPosition();
    }
    m_bMouseInJoyStickRect = false;
}

bool MusicPlayWidget::judgePointInRect(QPoint point)
{
    const Vec2f A = m_posACur;
    const Vec2f B = m_posBCur;
    const Vec2f C = m_posCCur;
    const Vec2f D = m_posDCur;

    //叉积 = x1*y2 - y1*x2
    const float a = (B.x - A.x)*(point.y() - A.y) - (B.y - A.y)*(point.x() - A.x);
    const float b = (C.x - B.x)*(point.y() - B.y) - (C.y - B.y)*(point.x() - B.x);
    const float c = (D.x - C.x)*(point.y() - C.y) - (D.y - C.y)*(point.x() - C.x);
    const float d = (A.x - D.x)*(point.y() - D.y) - (A.y - D.y)*(point.x() - D.x);

    if((a > 0 && b > 0 && c > 0 && d > 0) || (a < 0 && b < 0 && c < 0 && d < 0))
    {
        qDebug()<<"在范围内"<<Qt::endl;
        return true;
    }
    qDebug()<<"在范围外"<<Qt::endl;
    return false;
}

float MusicPlayWidget::caculateMouseMoveAngle(QPoint point)
{
    float startRad = atan2(m_lastMousePos.y() - CDJOYSTICK_POS_Y,
                           m_lastMousePos.x() - CDJOYSTICK_POS_X);

    float currRad = atan2(point.y() - CDJOYSTICK_POS_Y,
                          point.x() - CDJOYSTICK_POS_X);

    float angleDiff = (currRad - startRad) * 180.0f / MATH_PI;
    return angleDiff;
}

void MusicPlayWidget::updateCurrentJoyStickPosition()
{
    float rotateRad = m_joyStickRotAngle*MATH_PI/180;
    float posAX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthA;
    float posAY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthA;

    float posBX = CDJOYSTICK_POS_X - sin(m_angleBOrg+rotateRad)*m_lengthB;
    float posBY = CDJOYSTICK_POS_Y + cos(m_angleBOrg+rotateRad)*m_lengthB;

    float posCX = CDJOYSTICK_POS_X - sin(m_angleCOrg+rotateRad)*m_lengthC;
    float posCY = CDJOYSTICK_POS_Y + cos(m_angleCOrg+rotateRad)*m_lengthC;

    float posDX = CDJOYSTICK_POS_X - sin(m_angleDOrg+rotateRad)*m_lengthD;
    float posDY = CDJOYSTICK_POS_Y + cos(m_angleDOrg+rotateRad)*m_lengthD;

    m_posACur = Vec2f(posAX,posAY);
    m_posBCur = Vec2f(posBX,posBY);
    m_posCCur = Vec2f(posCX,posCY);
    m_posDCur = Vec2f(posDX,posDY);
}

void MusicPlayWidget::loadWidgetButton()
{
    m_pCurrentTimeLabel = new QLabel(this);
    m_pCurrentTimeLabel->setGeometry(15,15,50,25);
    m_pCurrentTimeLabel->setFont(QFont("Arial",20,50));
    m_pCurrentTimeLabel->setStyleSheet("background:transparent;font-size:20px;color:#ababab");
    m_pCurrentTimeLabel->setAlignment(Qt::AlignCenter);
    m_pCurrentTimeLabel->setText("1:31");

    m_pRemainTimeLabel = new QLabel(this);
    m_pRemainTimeLabel->setGeometry(MUSICPLAYWIDGET_WIDTH - 65,15,50,25);
    m_pRemainTimeLabel->setFont(QFont("Arial",20,50));
    m_pRemainTimeLabel->setStyleSheet("background:transparent;font-size:20px;color:#ababab");
    m_pRemainTimeLabel->setAlignment(Qt::AlignCenter);
    m_pRemainTimeLabel->setText("1:31");

    m_pPrevMusicButton = new QPushButton(this);
    m_pPrevMusicButton->move(85,MUSICPLAYWIDGET_HEIGHT - 190);
    m_pPrevMusicButton->setFixedSize(QSize(MUSICPLAYBUTTONWIDGET_WIDTH,MUSICPLAYBUTTONWIDGET_HEIGHT));
    m_pPrevMusicButton->setIcon(QIcon(":/images/Resources/previousButton.png"));
    m_pPrevMusicButton->setIconSize(QSize(MUSICPLAYBUTTONWIDGET_WIDTH,MUSICPLAYBUTTONWIDGET_HEIGHT));
    m_pPrevMusicButton->setFlat(true);
    m_pPrevMusicButton->setStyleSheet("QPushButton{background:transparent; border:none;} QPushButton:hover{background:transparent;} QPushButton:pressed{background:transparent;}");

    m_pNextMusicButton = new QPushButton(this);
    m_pNextMusicButton->move(310,MUSICPLAYWIDGET_HEIGHT - 190);
    m_pNextMusicButton->setFixedSize(QSize(MUSICPLAYBUTTONWIDGET_WIDTH,MUSICPLAYBUTTONWIDGET_HEIGHT));
    m_pNextMusicButton->setIcon(QIcon(":/images/Resources/nextButton.png"));
    m_pNextMusicButton->setIconSize(QSize(MUSICPLAYBUTTONWIDGET_WIDTH,MUSICPLAYBUTTONWIDGET_HEIGHT));
    m_pNextMusicButton->setFlat(true);
    m_pNextMusicButton->setStyleSheet("QPushButton{background:transparent; border:none;} QPushButton:hover{background:transparent;} QPushButton:pressed{background:transparent;}");

    m_pPlayMusicButton = new QPushButton(this);
    m_pPlayMusicButton->move(190,MUSICPLAYWIDGET_HEIGHT - 195);
    m_pPlayMusicButton->setFixedSize(QSize(MUSICPLAYBUTTONWIDGET_WIDTH + 16,MUSICPLAYBUTTONWIDGET_HEIGHT + 16));
    m_pPlayMusicButton->setIcon(QIcon(":/images/Resources/playButton.png"));
    m_pPlayMusicButton->setIconSize(QSize(MUSICPLAYBUTTONWIDGET_WIDTH + 16,MUSICPLAYBUTTONWIDGET_HEIGHT + 16));
    m_pPlayMusicButton->setFlat(true);
    m_pPlayMusicButton->setStyleSheet("QPushButton{background:transparent; border:none;} QPushButton:hover{background:transparent;} QPushButton:pressed{background:transparent;}");
}

void MusicPlayWidget::loadSliders()
{
    m_pMusicSlider = new MusicSeekSlider(this);
}
