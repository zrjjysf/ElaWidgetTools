#include "mainwindow.h"

#include "AlphaMainPage.h"
#include "ElaContentDialog.h"
#include "ElaMenu.h"
#include "ElaMenuBar.h"
#include "ElaStatusBar.h"
#include "ElaSuggestBox.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToolBar.h"
#include "ElaToolButton.h"
#include "T_About.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent)
{
    initWindow();
    initEdgeLayout();
    initContent();

    _closeDialog = new ElaContentDialog(this);
    connect(_closeDialog, &ElaContentDialog::rightButtonClicked, this, &MainWindow::close);
    connect(_closeDialog, &ElaContentDialog::middleButtonClicked, this, [this]() {
        _closeDialog->close();
        showMinimized();
    });
    setIsDefaultClosed(false);
    connect(this, &MainWindow::closeButtonClicked, this, [this]() {
        _closeDialog->exec();
    });
}

MainWindow::~MainWindow()
{
}

void MainWindow::initWindow()
{
    resize(1440, 920);
    setWindowTitle("Binance Shell Alpha Monitor");
    setUserInfoCardTitle("Alpha Monitor");
    setUserInfoCardSubTitle("BinanceShell / Qt View");
    setNavigationBarDisplayMode(ElaNavigationType::Compact);
    addCentralWidget(new QWidget(this));

    QWidget* centralCustomWidget = new QWidget(this);
    QHBoxLayout* centralLayout = new QHBoxLayout(centralCustomWidget);
    centralLayout->setContentsMargins(13, 12, 9, 6);

    _windowSuggestBox = new ElaSuggestBox(this);
    _windowSuggestBox->setFixedHeight(34);
    _windowSuggestBox->setPlaceholderText("搜索页面");

    ElaToolButton* themeButton = new ElaToolButton(this);
    themeButton->setElaIcon(ElaIconType::MoonStars);
    connect(themeButton, &ElaToolButton::clicked, this, []() {
        eTheme->setThemeMode(eTheme->getThemeMode() == ElaThemeType::Light ? ElaThemeType::Dark : ElaThemeType::Light);
    });

    ElaText* hintText = new ElaText("手动刷新取数，不做轮询", this);
    hintText->setTextPixelSize(14);

    centralLayout->addWidget(_windowSuggestBox, 1);
    centralLayout->addWidget(hintText);
    centralLayout->addWidget(themeButton);
    setCentralCustomWidget(centralCustomWidget);
}

void MainWindow::initEdgeLayout()
{
    ElaMenuBar* menuBar = new ElaMenuBar(this);
    menuBar->setFixedHeight(30);

    ElaMenu* actionMenu = menuBar->addMenu("操作");
    actionMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新当前页");
    actionMenu->addElaIconAction(ElaIconType::MoonStars, "切换主题");

    QWidget* topWidget = new QWidget(this);
    QVBoxLayout* topLayout = new QVBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(menuBar);
    topLayout->addStretch();
    setCustomWidget(ElaAppBarType::MiddleArea, topWidget);

    ElaToolBar* toolBar = new ElaToolBar("Alpha Toolbar", this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->setIconSize(QSize(20, 20));

    ElaToolButton* homeButton = new ElaToolButton(this);
    homeButton->setElaIcon(ElaIconType::Table);
    homeButton->setText("Alpha");
    connect(homeButton, &ElaToolButton::clicked, this, [this]() {
        if (_alphaPage)
        {
            navigation(_alphaPage->property("ElaPageKey").toString());
        }
    });
    toolBar->addWidget(homeButton);

    ElaToolButton* aboutButton = new ElaToolButton(this);
    aboutButton->setElaIcon(ElaIconType::CircleInfo);
    aboutButton->setText("About");
    connect(aboutButton, &ElaToolButton::clicked, this, [this]() {
        if (_aboutPage)
        {
            _aboutPage->moveToCenter();
            _aboutPage->show();
        }
    });
    toolBar->addWidget(aboutButton);
    addToolBar(Qt::TopToolBarArea, toolBar);

    ElaStatusBar* statusBar = new ElaStatusBar(this);
    ElaText* statusText = new ElaText("Alpha UI ready", this);
    statusText->setTextPixelSize(13);
    statusBar->addWidget(statusText);
    setStatusBar(statusBar);
}

void MainWindow::initContent()
{
    _alphaPage = new AlphaMainPage(this);
    addPageNode("Alpha Monitor", _alphaPage, ElaIconType::Table);

    addFooterNode("About", nullptr, _aboutKey, 0, ElaIconType::CircleInfo);
    _aboutPage = new T_About(this);
    _aboutPage->hide();

    connect(this, &ElaWindow::navigationNodeClicked, this, [this](ElaNavigationType::NavigationNodeType, const QString& nodeKey) {
        if (nodeKey == _aboutKey && _aboutPage)
        {
            _aboutPage->moveToCenter();
            _aboutPage->show();
        }
    });

    connect(this, &MainWindow::userInfoCardClicked, this, [this]() {
        if (_alphaPage)
        {
            navigation(_alphaPage->property("ElaPageKey").toString());
        }
    });

    _windowSuggestBox->addSuggestion(getNavigationSuggestDataList());
    connect(_windowSuggestBox, &ElaSuggestBox::suggestionClicked, this, [this](const ElaSuggestBox::SuggestData& suggestData) {
        navigation(suggestData.getSuggestData().value("ElaPageKey").toString());
    });
}
