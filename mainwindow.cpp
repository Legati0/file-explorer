#include "mainwindow.h"
#include "explorerwidget.h"
#include "navwidget.h"
#include "renamedialog.h"
#include "mkdirdialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <iostream>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QAction>
#include <QMenu>
#include <QFile>
#include <QThread>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QProcess>
#include <QPair>
#include <QToolButton>
#include "contentwidget.h"

MainWindow::MainWindow(QDir startDir)
{
    QFileIconProvider provider;
    tabs = new QTabWidget();
    QIcon icon = QIcon::fromTheme(QLatin1String("tab-new"));
    QToolButton *btn = new QToolButton();
    btn->setIcon(icon);
    connect(btn, &QToolButton::clicked, this, &MainWindow::onNewTab);
    tabs->setCornerWidget(btn, Qt::TopRightCorner);
    connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabClose);
    setCentralWidget(tabs);

    auto w = new ContentWidget(startDir);
    tabs->addTab(w, w->dirName());
    tabs->setTabIcon(0, provider.icon(QFileInfo(w->absolutePath())));
    connect(w, &ContentWidget::dirChanged, this, &MainWindow::onDirChanged);

    connect(tabs, &QTabWidget::currentChanged, this, &MainWindow::onTabChange);
}

void MainWindow::setTitle(QString s) {
    setWindowTitle("Explorer - " + s);
}

void MainWindow::onTabChange(int index) {
        setTitle(tabs->tabText(index));
}

void MainWindow::onDirChanged(QDir& dir) {
    std::cout << "dir changed" << std::endl;
    auto name = dir.dirName();
    if (name.isEmpty())
        name = "/";
    setTitle(name);
    auto index = tabs->currentIndex();
    tabs->setTabText(index, name);
    tabs->setTabIcon(index, provider.icon(QFileInfo(dir.absolutePath())));
}

void MainWindow::onNewTab() {
    auto dir = QDir::home();
    auto w = new ContentWidget(dir);
    tabs->addTab(w, provider.icon(QFileInfo(dir.absolutePath())), dir.dirName());
    tabs->setCurrentWidget(w);
    tabs->setTabsClosable(true);
    connect(w, &ContentWidget::dirChanged, this, &MainWindow::onDirChanged);
}

void MainWindow::onTabClose(int index) {
    if (index == -1)
        return;
    if (tabs->count() == 1)
        return;
    auto tabItem = tabs->widget(index);
    tabs->removeTab(index);
    delete tabItem;
    tabItem = nullptr;
    if (tabs->count() == 1)
        tabs->setTabsClosable(false);
}

MainWindow::~MainWindow() {}
