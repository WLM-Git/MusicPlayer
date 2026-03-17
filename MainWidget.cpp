#include "MainWidget.h"
#include <QScreen>
#include <QPainter>
#include <QPushButton>

#define MAINWDIGET_WIDTH 480
#define MAINWDIGET_HEIGHT 856
#define TOPBUTTON_WIDTH 70
#define TOPBUTTON_HEIGHT 50

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGemotery = screen->availableGeometry();
    int startX = (screenGemotery.width() - MAINWDIGET_WIDTH)/2;
    int startY = (screenGemotery.height() - MAINWDIGET_HEIGHT)/2;

    setGeometry(startX,startY,MAINWDIGET_WIDTH,MAINWDIGET_HEIGHT);
    loadTopButton();
    loadTopLabel();
    loadMusicPlayWidget();
}

MainWidget::~MainWidget() {}

void MainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(rect(),QPixmap(":/images/Resources/musicPlayerPageBg.png"));
    return;
}

void MainWidget::loadTopButton()
{
    QPushButton* backButton = new QPushButton(this);
    backButton->move(18,37);
    backButton->setFixedSize(TOPBUTTON_WIDTH,TOPBUTTON_HEIGHT);
    backButton->setIcon(QIcon(":/images/Resources/backButton.png"));
    backButton->setIconSize(QSize(TOPBUTTON_WIDTH,TOPBUTTON_HEIGHT));
    backButton->setFlat(true);
    backButton->setAutoFillBackground(true);
    backButton->setStyleSheet("QPushButton{background:transparent}");

    QPushButton* listButton = new QPushButton(this);
    listButton->move(MAINWDIGET_WIDTH-18-TOPBUTTON_WIDTH,37);
    listButton->setFixedSize(TOPBUTTON_WIDTH,TOPBUTTON_HEIGHT);
    listButton->setIcon(QIcon(":/images/Resources/musicListButton.png"));
    listButton->setIconSize(QSize(TOPBUTTON_WIDTH,TOPBUTTON_HEIGHT));
    listButton->setFlat(true);
    listButton->setAutoFillBackground(true);
    listButton->setStyleSheet("QPushButton{background:transparent}");
}

void MainWidget::loadTopLabel()
{
    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setGeometry(120,40,MAINWDIGET_WIDTH - 240,30);
    m_pTitleLabel->setFont(QFont("Arial",20,50));
    m_pTitleLabel->setStyleSheet("background:transparent;font-size:20px;color:white");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setText("勇敢的心");

    m_pAuthorLabel = new QLabel(this);
    m_pAuthorLabel->setGeometry(120,70,MAINWDIGET_WIDTH - 240,30);
    m_pAuthorLabel->setFont(QFont("Arial",15,50));
    m_pAuthorLabel->setStyleSheet("background:transparent;font-size:15px;color:white");
    m_pAuthorLabel->setAlignment(Qt::AlignCenter);
    m_pAuthorLabel->setText("勇敢的心");
}

void MainWidget::loadMusicPlayWidget()
{
    m_pMusicPlayWidget = new MusicPlayWidget(this);
    connect(m_pMusicPlayWidget,&MusicPlayWidget::updateMusicMetaInformation,this,&MainWidget::onUpdateMusicMetaInformation);
}

void MainWidget::onUpdateMusicMetaInformation(MusicInfo *musicInfo)
{
    if(musicInfo == nullptr)
        return;
    m_pTitleLabel->setText(musicInfo->musicTitle);
    m_pAuthorLabel->setText(musicInfo->musicAuthor);
}
