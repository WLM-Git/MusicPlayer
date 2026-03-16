#ifndef MUSICPLAYWIDGET_H
#define MUSICPLAYWIDGET_H

#include <QWidget>
#include "Vec2f.h"
#include <QLabel>
#include <QPushButton>
#include "musicseekslider.h"
#include "volumechangeslider.h"
#include <QTimer>
#include "vlc/vlc.h"

#define MATH_PI 3.1415926f

class MusicPlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayWidget(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    bool judgePointInRect(QPoint point);
    float caculateMouseMoveAngle(QPoint point);
    void updateCurrentJoyStickPosition();

    void loadWidgetButton();
    void loadSliders();

    void onMusicTimerProcess();
    void onPlayMusicButtonClicked();

private:
    float       m_angleAOrg = 15.0f * MATH_PI/180;
    float       m_angleBOrg = 11.0f * MATH_PI/180;
    float       m_angleCOrg = 6.0f * MATH_PI/180;
    float       m_angleDOrg = 11.0f * MATH_PI/180;

    float       m_lengthA = 357.0f;
    float       m_lengthB = 370.0f;
    float       m_lengthC = 318.0f;
    float       m_lengthD = 302.0f;

    Vec2f       m_posAOrg = Vec2f();
    Vec2f       m_posBOrg = Vec2f();
    Vec2f       m_posCOrg = Vec2f();
    Vec2f       m_posDOrg = Vec2f();

    Vec2f       m_posACur = Vec2f();
    Vec2f       m_posBCur = Vec2f();
    Vec2f       m_posCCur = Vec2f();
    Vec2f       m_posDCur = Vec2f();

    float       m_joyStickRotAngle = 0.0f;
    float       m_cdRotateAngle = 0.0f;

    QPoint      m_lastMousePos = QPoint(0,0);
    bool        m_bMouseInJoyStickRect = false;
    float       m_mouseMoveAngle = 0.0f;
    float       m_mouseLastAngle = 0.0f;

    QLabel*                 m_pCurrentTimeLabel;
    QLabel*                 m_pRemainTimeLabel;
    QPushButton*            m_pPrevMusicButton;
    QPushButton*            m_pNextMusicButton;
    QPushButton*            m_pPlayMusicButton;
    MusicSeekSlider*        m_pMusicSlider;
    VolumeChangeSlider*     m_pVolumeSlider;

    QTimer*                 m_pMusicPlayerTimer;
    bool                    m_bTimerPlaying;

signals:
};

#endif // MUSICPLAYWIDGET_H
