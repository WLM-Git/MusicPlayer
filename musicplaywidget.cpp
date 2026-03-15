#include "musicplaywidget.h"
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

    float rotateRad = m_joyStickRotAngle*MATH_PI/180;
    float posAX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthA;
    float posAY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthA;

    float posBX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthB;
    float posBY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthB;

    float posCX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthC;
    float posCY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthC;

    float posDX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthD;
    float posDY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthD;

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
    if((event->buttons() & Qt::LeftButton))
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

}

float MusicPlayWidget::caculateMouseMoveAngle(QPoint point)
{

}

void MusicPlayWidget::updateCurrentJoyStickPosition()
{
    float rotateRad = m_joyStickRotAngle*MATH_PI/180;
    float posAX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthA;
    float posAY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthA;

    float posBX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthB;
    float posBY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthB;

    float posCX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthC;
    float posCY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthC;

    float posDX = CDJOYSTICK_POS_X - sin(m_angleAOrg+rotateRad)*m_lengthD;
    float posDY = CDJOYSTICK_POS_Y + cos(m_angleAOrg+rotateRad)*m_lengthD;

    m_posACur = Vec2f(posAX,posAY);
    m_posBCur = Vec2f(posBX,posBY);
    m_posCCur = Vec2f(posCX,posCY);
    m_posDCur = Vec2f(posDX,posDY);
}
