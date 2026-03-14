#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
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
private:
    QLabel* m_pTitleLabel;
    QLabel* m_pAuthorLabel;

};
#endif // MAINWIDGET_H
