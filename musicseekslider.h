#ifndef MUSICSEEKSLIDER_H
#define MUSICSEEKSLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QMouseEvent>


class MusicSliderHandle : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSliderHandle(QWidget *parent = nullptr);
    virtual ~MusicSliderHandle();
private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QPointF m_lastMousePoisition;

signals:
    void musicSliderMoveSignal(int);
    void musicSliderReleaseSignal();
};

class MusicSeekSlider : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSeekSlider(QWidget *parent = nullptr);
    void SetUpMusicSeekSliderValue(int value);
private:
    int                     m_currentPoxX;
    MusicSliderHandle*      m_pMusicSeekHandle;
    QPoint                  m_originalPos;
    int                     m_currentPosX;
    bool                    m_bHandleMoving;
private:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void onSliderHandleMove(int posX);
    void onSliderHandleRelease();

signals:
    void updateMusicSeekValueSignal(int value);
};

#endif // MUSICSEEKSLIDER_H
