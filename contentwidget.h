#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QDir>
#include <QStack>
#include "navwidget.h"
#include "explorerwidget.h"


class ContentWidget : public QWidget
{
    Q_OBJECT
private:
    QDir dir;
    QStack<QString> history;
    QStack<QString> future;
    NavWidget* nav;
    ExplorerWidget* explorer;
    // slots
    void onUp();
    void onBack();
    void onForward();
    void onNavEnter();
    void onExplorerClick(QTreeWidgetItem* item);
    void onMkdir();
    // internal methods
    void cd(QString dirStr);
    void updateWidgets();
    // menus and dialogs
    void prepareMenu(const QPoint& pos);
    void mkdirDialog();
    void renameDialog(QString fname);
    void rmDialog(QString fname);
    void openTerminal();

public:
    ContentWidget(QDir dir);
    virtual ~ContentWidget();

    QDir currentDir() const;
    QString dirName() const;
    QString absolutePath() const;

signals:
    void dirChanged(QDir& dir);

};

#endif // CONTENTWIDGET_H
