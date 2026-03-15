#ifndef MUSICSEEKSLIDER_H
#define MUSICSEEKSLIDER_H

#include <QWidget>
#include <QMouseEvent>

class MusicSliderHandle : QWidget
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
    QPoint m_lastMousePoisition;

signals:
    void musicSliderMoveSignal(int);
    void musicSliderMoveDoneSignal();
};

class MusicSeekSlider : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSeekSlider(QWidget *parent = nullptr);

signals:
};

#endif // MUSICSEEKSLIDER_H
