#include "musicseekslider.h"
#include <QPainter>

#define MUSICSLIDERHANDLE_WIDTH     20
#define MUSICSLIDERHANDLE_HEIGHT    20

#define MUSICSEEKSLIDER_WIDTH   344
#define MUSICSEEKSLIDER_HEIGHT   18

MusicSliderHandle::MusicSliderHandle(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(0,-1,MUSICSLIDERHANDLE_WIDTH,MUSICSLIDERHANDLE_HEIGHT);
}

MusicSliderHandle::~MusicSliderHandle()
{
}

void MusicSliderHandle::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_lastMousePoisition = event->globalPosition();
    }
    return;
}

void MusicSliderHandle::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF curPos = event->globalPosition();
        QPointF diffPos = curPos -  m_lastMousePoisition;
        m_lastMousePoisition = curPos;
        emit musicSliderMoveSignal(diffPos.x());
    }
    return;
}


void MusicSliderHandle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(rect(),QPixmap(":/images/Resources/musicSeekButton.png"));
    return;
}

/*--------------------------------------------------*/
/*--------------------------------------------------*/
/*--------------------------------------------------*/

MusicSeekSlider::MusicSeekSlider(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(68,17,MUSICSEEKSLIDER_WIDTH,MUSICSEEKSLIDER_HEIGHT);
    m_pMusicSeekHandle = new MusicSliderHandle(this);
    connect(m_pMusicSeekHandle,&MusicSliderHandle::musicSliderMoveSignal,this,&MusicSeekSlider::onSliderHandleMove);
    m_originalPos = m_pMusicSeekHandle->pos();
    m_currentPosX = m_originalPos.x();
}

void MusicSeekSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(rect(),QPixmap(":/images/Resources/musicProgressBg.png"));

    painter.save();
    painter.setPen(QPen(QColor(136,135,140),1));
    painter.setBrush(QColor(136,135,140));
    painter.drawEllipse(0,2,14,14);
    painter.drawRect(6,1,m_pMusicSeekHandle->pos().x(),MUSICSEEKSLIDER_HEIGHT);
    painter.restore();

    return;
}

void MusicSeekSlider::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(m_pMusicSeekHandle == nullptr)
            return;
        m_currentPosX = event->pos().x();
        if(m_currentPosX < 0)
        {
            m_currentPosX = 0;
        }
        else if(m_currentPosX > 324)
        {
            m_currentPosX = 324;
        }
        m_pMusicSeekHandle->move(m_currentPosX,m_originalPos.y());
        update();
    }
    return;
}

void MusicSeekSlider::onSliderHandleMove(int posX)
{
    if(m_pMusicSeekHandle == nullptr)
        return;

    m_currentPosX += posX;
    if(m_currentPosX < 0)
    {
        m_currentPosX = 0;
    }
    else if(m_currentPosX > 324)
    {
        m_currentPosX = 324;
    }

    m_pMusicSeekHandle->move(m_currentPosX, m_originalPos.y());
    update();
}


