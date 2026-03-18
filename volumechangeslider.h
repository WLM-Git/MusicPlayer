#ifndef VOLUMECHANGESLIDER_H
#define VOLUMECHANGESLIDER_H

#include <QWidget>
#include <QMouseEvent>


class VolumeSliderHandle : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeSliderHandle(QWidget *parent = nullptr);
    virtual ~VolumeSliderHandle();
private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPointF m_lastMousePoisition;

signals:
    void volumechangeSliderMoveSignal(int);
};

class VolumeChangeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeChangeSlider(QWidget *parent = nullptr);
private:
    int                         m_currentPoxX;
    VolumeSliderHandle*   m_pVolumeChangeHandle;
    QPoint                      m_originalPos;
    int                         m_currentPosX;
private:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

public slots:
    void onSliderHandleMove(int posX);

signals:
    void volumeSliderValueChangeSignal(int);
};

#endif // VOLUMECHANGESLIDER_H
