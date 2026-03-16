#include "volumechangeslider.h"
#include <QPainter>

#define VOLUMESLIDERHANDLE_WIDTH     31
#define VOLUMESLIDERHANDLE_HEIGHT    48

#define VOLUMECHANGESLIDER_WIDTH     414
#define VOLUMECHANGESLIDER_HEIGHT    45
#define MUSICSCREEN_HEIGHT           756

VolumeSliderHandle::VolumeSliderHandle(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(0,0,VOLUMESLIDERHANDLE_WIDTH,VOLUMESLIDERHANDLE_HEIGHT);
}

VolumeSliderHandle::~VolumeSliderHandle()
{
}

void VolumeSliderHandle::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_lastMousePoisition = event->globalPosition();
    }
    return;
}

void VolumeSliderHandle::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF curPos = event->globalPosition();
        QPointF diffPos = curPos -  m_lastMousePoisition;
        m_lastMousePoisition = curPos;
        emit volumechangeSliderMoveSignal(diffPos.x());
    }
    return;
}


void VolumeSliderHandle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(rect(),QPixmap(":/images/Resources/volumeButton.png"));
    return;
}

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/*--------------------------------------------------*/

VolumeChangeSlider::VolumeChangeSlider(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(38,MUSICSCREEN_HEIGHT - 79,VOLUMECHANGESLIDER_WIDTH,VOLUMECHANGESLIDER_HEIGHT);
    m_pVolumeChangeHandle = new VolumeSliderHandle(this);
    connect(m_pVolumeChangeHandle,&VolumeSliderHandle::volumechangeSliderMoveSignal,this,&VolumeChangeSlider::onSliderHandleMove);
    m_originalPos = m_pVolumeChangeHandle->pos();
    m_currentPosX = m_originalPos.x();
}

void VolumeChangeSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(rect(),QPixmap(":/images/Resources/volumeBackground.png"));

    painter.save();
    painter.setPen(QPen(QColor(138, 139, 143), 1));
    painter.setBrush(QColor(138, 139, 143));
    painter.drawRoundedRect(13, 16, 14,14,2,2);
    painter.drawRect(18, 16, m_pVolumeChangeHandle->pos().x(),14);
    painter.restore();
}

void VolumeChangeSlider::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(m_pVolumeChangeHandle == nullptr)
            return;
        m_currentPosX = event->pos().x();
        if(m_currentPosX < 0)
        {
            m_currentPosX = 0;
        }
        else if(m_currentPosX > 383)
        {
            m_currentPosX = 383;
        }

        m_pVolumeChangeHandle->move(m_currentPosX,m_originalPos.y());
        update();
    }
    return;
}

void VolumeChangeSlider::onSliderHandleMove(int posX)
{
    if(m_pVolumeChangeHandle == nullptr)
        return;
    m_currentPosX += posX;
    if(m_currentPosX < 0)
    {
        m_currentPosX = 0;
    }
    else if(m_currentPosX > 383)
    {
        m_currentPosX = 383;
    }

    m_pVolumeChangeHandle->move(m_currentPosX,m_originalPos.y());
    update();
}


