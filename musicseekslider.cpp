#include "musicseekslider.h"
#include <QPainter>

#define MUSICSLIDERHANDLE_WIDTH     20
#define MUSICSLIDERHANDLE_HEIGHT    20


MusicSliderHandle::MusicSliderHandle(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(0,0,MUSICSLIDERHANDLE_WIDTH,MUSICSLIDERHANDLE_HEIGHT);
}

MusicSliderHandle::~MusicSliderHandle()
{

}

void MusicSliderHandle::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_lastMousePoisition = event->pos();
    }
    return;
}

void MusicSliderHandle::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint curPos = event->pos();
        QPoint diffPos = curPos -  m_lastMousePoisition;
        m_lastMousePoisition = curPos;
        emit musicSliderMoveSignal(diffPos.x());
    }
    return;
}

void MusicSliderHandle::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit musicSliderMoveDoneSignal();
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

MusicSeekSlider::MusicSeekSlider(QWidget *parent)
    : QWidget{parent}
{}


