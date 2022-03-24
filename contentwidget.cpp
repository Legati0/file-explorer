#include "contentwidget.h"
#include "mkdirdialog.h"
#include "renamedialog.h"

#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <iostream>
#include <QMessageBox>
#include <QProcess>
#include <QProcessEnvironment>
#include <QDesktopServices>
#include <QUrl>
#include <QListWidget>
#include <QPushButton>

ContentWidget::ContentWidget(QDir dir)
    : dir(dir)
{
    auto layout = new QVBoxLayout();

    nav = new NavWidget();
    //this->setMenuWidget(nav);
    layout->addWidget(nav);
    QFileIconProvider provider;

    auto hLayout = new QHBoxLayout();

    auto style = QString("QPushButton { border: none; } QPushButton:hover {background-color: #222;}");
    auto list = new QVBoxLayout();
    auto placesLbl = new QLabel("Places");
    list->addWidget(placesLbl);
    auto homeBtn = new QPushButton("Home");
    homeBtn->setStyleSheet(style);
    homeBtn->setIcon(provider.icon(QFileInfo(QDir::homePath())));
    list->addWidget(homeBtn);
    auto desktopBtn = new QPushButton("Desktop");
    desktopBtn->setStyleSheet(style);
    desktopBtn->setIcon(provider.icon(QFileInfo(QDir::homePath() + "/Desktop/")));
    list->addWidget(desktopBtn);
    auto documentsBtn = new QPushButton("Documents");
    documentsBtn->setStyleSheet(style);
    documentsBtn->setIcon(provider.icon(QFileInfo(QDir::homePath() + "/Documents/")));
    list->addWidget(documentsBtn);
    auto downloadsBtn = new QPushButton("Downloads");
    downloadsBtn->setStyleSheet(style);
    downloadsBtn->setIcon(provider.icon(QFileInfo(QDir::homePath() + "/Downloads/")));
    list->addWidget(downloadsBtn);
    auto musicBtn = new QPushButton("Music");
    musicBtn->setStyleSheet(style);
    musicBtn->setIcon(provider.icon(QFileInfo(QDir::homePath() + "/Music/")));
    list->addWidget(musicBtn);
    //hLayout->addLayout(list);

    explorer = new ExplorerWidget();
    //this->setCentralWidget(explorer);
    hLayout->addWidget(explorer);

    layout->addLayout(hLayout);

    setLayout(layout);

    updateWidgets();

    // connect up dir
    connect(nav->getUpBtn(), &QPushButton::clicked, this, &ContentWidget::onUp);
    // connect back
    connect(nav->getBackBtn(), &QPushButton::clicked, this, &ContentWidget::onBack);
    // connect forward
    connect(nav->getForwardBtn(), &QPushButton::clicked, this, &ContentWidget::onForward);
    // connect doubleclick goto
    connect(explorer, &ExplorerWidget::itemDoubleClicked, this, &ContentWidget::onExplorerClick);
   // connect nav enter goto
    connect(nav->getEdit(), &QLineEdit::returnPressed, this, &ContentWidget::onNavEnter);
    // connect right-click context menu
    connect(explorer, &QTreeWidget::customContextMenuRequested, this, &ContentWidget::prepareMenu);
   // connect new dir btn to new dir dialog
    connect(nav->getMkdirBtn(), &QPushButton::clicked, this, &ContentWidget::onMkdir);
}

void ContentWidget::prepareMenu( const QPoint & pos ) {
    QFileIconProvider provider;
    QTreeWidgetItem *nd = explorer->itemAt(pos);
    QMenu menu(this);

    auto newMenu = menu.addMenu("Create New...");

    auto mkdirAct = new QAction("New Dir", this);
    mkdirAct->setStatusTip("mkdir statustip");
    // TODO: not working
    mkdirAct->setIcon(provider.icon(QFileIconProvider::Folder));
    connect(mkdirAct, &QAction::triggered, this, &ContentWidget::onMkdir);
    newMenu->addAction(mkdirAct);

    auto newTxtAct = new QAction("New txt file", this);
    newTxtAct->setStatusTip("new txt statustip");
    mkdirAct->setIcon(provider.icon(QFileInfo("file.txt")));
    //connect(mkdirAct, &QAction::triggered, this, &MainWindow::onMkdir);
    newMenu->addAction(newTxtAct);

    menu.addSeparator();

    // if item -> remove, rename
    if (nd != nullptr) {
        auto name = nd->text(0);
        std::cout << name.toStdString() << std::endl;

        auto renameAct = new QAction("rename", this);
        renameAct->setStatusTip("rename statustip");
        connect(renameAct, &QAction::triggered, this, [name, this]{ renameDialog(name); });
        menu.addAction(renameAct);

        auto rmAct = new QAction("delete", this);
        rmAct->setStatusTip("delete statustip");
        connect(rmAct, &QAction::triggered, this, [name, this]{ rmDialog(name); });
        menu.addAction(rmAct);
    }

    menu.addSeparator();

    auto terminalAct = new QAction("terminal here", this);
    terminalAct->setStatusTip("open terminal in this dir");
    connect(terminalAct, &QAction::triggered, this, &ContentWidget::openTerminal);
    menu.addAction(terminalAct);

    menu.addSeparator();
    //properties

    //QPoint pt(pos);
    menu.exec(explorer->mapToGlobal(pos));
}

void ContentWidget::renameDialog(QString fname) {
    std::cout << this->dir.absolutePath().toStdString() << std::endl;
    std::cout << fname.toStdString() << std::endl;

    RenameDialog d(this);
    d.setFile(fname);
    d.exec();

    if (d.isCanceled())
        return;
    auto newName = d.text();
    if (newName == fname)
        return;
    if (newName.isEmpty())
        return;

    std::cout << "------------------" << std::endl;
    auto oldFname = this->dir.absolutePath() + dir.separator() + fname;
    std::cout << oldFname.toStdString() << std::endl;
    auto newFname = this->dir.absolutePath() + dir.separator() + newName;
    std::cout << newFname.toStdString() << std::endl;
    QFile file(oldFname);
    if (!file.rename(newFname))
        std::cout << "rename failed" << std::endl;
    dir.refresh();
    updateWidgets();
}

void ContentWidget::mkdirDialog() {
    MkdirDialog d(this);
    d.exec();

    if (d.isCanceled())
        return;
    QString name = d.text();
    if (name.isEmpty())
        return;
    dir.mkdir(name);
    dir.refresh();
    updateWidgets();
}

void ContentWidget::rmDialog(QString fname) {
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Remove?", QString("Are you sure you want to remove '%1'?").arg(fname),
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          dir.rmpath(dir.absolutePath() + dir.separator() + fname);
          dir.refresh();
          updateWidgets();
      } else {
          std::cout << "not removed" << std::endl;
      }
}

QDir ContentWidget::currentDir() const {
    return dir;
}
QString ContentWidget::dirName() const {
    return dir.dirName();
}
QString ContentWidget::absolutePath() const {
    return dir.absolutePath();
}

void ContentWidget::onUp() {
    std::cout << "up" << std::endl;
    if (dir.absolutePath() == "/")
        return;
    this->history.push(dir.absolutePath());
    dir.cdUp();
    updateWidgets();
}

void ContentWidget::onBack() {
    std::cout << "back" << std::endl;
    if (history.empty())
        return;
    this->future.push(dir.absolutePath());
    this->dir.cd(this->history.pop());
    updateWidgets();
}

void ContentWidget::onForward() {
    std::cout << "forward" << std::endl;
    if (future.empty())
        return;
    this->history.push(dir.absolutePath());
    this->dir.cd(this->future.pop());
    updateWidgets();
}

void ContentWidget::onNavEnter() {
    auto s = nav->getEdit()->text();
    if (dir.exists(s))
        cd(s);
}

void ContentWidget::onExplorerClick(QTreeWidgetItem* item) {
    //std::cout << item->text(0).toStdString() << std::endl;
    auto s = dir.absolutePath() + dir.separator() + item->text(0);
    QFileInfo f(s);
    if (f.exists() && f.isFile())
        QDesktopServices::openUrl(QUrl("file://" + f.absoluteFilePath()));
   else if (dir.exists(s))
        cd(s);
}

void ContentWidget::onMkdir() {
    mkdirDialog();
}

void ContentWidget::cd(QString dirStr) {
    this->history.push(dir.absolutePath());
    this->future.clear();
    this->dir.cd(dirStr);
    updateWidgets();
}

void ContentWidget::updateWidgets() {
    //std::cout << "history" << toStr(history).toStdString() << std::endl;
    //std::cout << "future" << toStr(future).toStdString() << std::endl;
    this->nav->updateText(this->dir.absolutePath());
    this->explorer->updateList(this->dir);
    emit dirChanged(dir);
    //this->setWindowTitle("Explorer - " + dir.dirName());
}

void ContentWidget::openTerminal() {
    const auto pathDirs = QProcessEnvironment::systemEnvironment().value("PATH").split(':');
    const QStringList terms = {"$TERMINAL",  "x-terminal-emulator", "mate-terminal", "gnome-terminal",
                         "terminator", "xfce4-terminal", "urxvt", "rxvt", "termit", "Eterm", "aterm", "uxterm",
                         "xterm", "roxterm", "termite", "lxterminal", "terminology", "st", "qterminal", "lilyterm",
                         "tilix", "terminix", "konsole", "kitty", "guake", "tilda", "alacritty", "hyper"};

    for (auto s : pathDirs) {
        QDir d(s);
        auto entries = d.entryList();
        for (auto term : terms) {
            if (entries.contains(term)) {
                QProcess p;
                p.setProgram(term);
                p.setWorkingDirectory(dir.absolutePath());
                p.startDetached();
                std::cout << "this term is in path: " << term.toStdString() << std::endl;
                return;
            }
        }
    }
}

ContentWidget::~ContentWidget() {}

