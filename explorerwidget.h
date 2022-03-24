#ifndef EXPLORERWIDGET_H
#define EXPLORERWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QTreeWidget>
#include <QFileIconProvider>
#include <QDir>


class ExplorerWidget : public QTreeWidget
{
    Q_OBJECT

private:
    QFileIconProvider provider;
    static QString fileSizeSI(qint64 bytes);
    static QString fileSizeIEC(qint64 bytes);
public:
    ExplorerWidget(QWidget* parent=nullptr);
    virtual ~ExplorerWidget();

    void updateList(QDir& dir);

signals:

};

#endif // EXPLORERWIDGET_H
