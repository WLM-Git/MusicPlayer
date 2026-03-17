#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include "musicplaywidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    void paintEvent(QPaintEvent* event) override;
    void loadTopButton();
    void loadTopLabel();
    void loadMusicPlayWidget();
private:
    QLabel*                 m_pTitleLabel;
    QLabel*                 m_pAuthorLabel;
    MusicPlayWidget*        m_pMusicPlayWidget;
private slots:
    void onUpdateMusicMetaInformation(MusicInfo* musicInfo);
};
#endif // MAINWIDGET_H
