#include "musicplaywidget.h"
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

}
