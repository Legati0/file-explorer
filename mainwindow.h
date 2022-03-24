#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStack>
#include <QVector>
#include <QTabWidget>
#include "navwidget.h"
#include "explorerwidget.h"
#include <QTreeWidgetItem>
#include <QFileIconProvider>

class NavWidget;
class ExplorerWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QFileIconProvider provider;
    QTabWidget* tabs;
    void setTitle(QString s);
    void onTabClose(int index);
    void onNewTab();
    void onDirChanged(QDir& dir);
    void onTabChange(int index);

public:
    MainWindow(QDir startDir=QDir::homePath());
    virtual ~MainWindow();

};
#endif // MAINWINDOW_H
