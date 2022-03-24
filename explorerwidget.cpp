#include "explorerwidget.h"
#include <QTableView>
#include <QDir>
#include <iostream>
#include <QDateTime>
#include <QFileIconProvider>
#include <cmath>
#include "customtreewidgetitem.h"

QString ExplorerWidget::fileSizeSI(qint64 bytes) {
    // stolen from https://stackoverflow.com/questions/10420352/converting-file-size-in-bytes-to-human-readable-string
    if (bytes == 0) return QString("0.00 B");
    int ind = log(bytes) / log(1000);
    return QString::number(bytes / pow(1000, ind), 'f', 2) + " " + (ind > 0  ? QString("kMGTPEZY").at(ind - 1) : QChar())+ "B";
}
QString ExplorerWidget::fileSizeIEC(qint64 bytes) {
    // stolen from https://stackoverflow.com/questions/10420352/converting-file-size-in-bytes-to-human-readable-string
    if (bytes == 0) return QString("0.00 B");
    int ind = log(bytes) / log(1024);
    return QString::number(bytes / pow(1000, ind), 'f', 2) + " " + (ind > 0 ? QString("kMGTPEZY").at(ind - 1) : QChar())+ "iB";
}


ExplorerWidget::ExplorerWidget(QWidget *parent)
    : QTreeWidget{parent}
{

    this->setColumnCount(3);
    this->setHeaderLabels({"name", "size", "modified"});
    this->setSortingEnabled(true);
    this->setExpandsOnDoubleClick(false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //this->resizeColumnToContents(0);
    auto w = this->width() * 3/4;
    this->setColumnWidth(0, int(w/2));
    this->setColumnWidth(1, int(w/4));
    this->setColumnWidth(2, int(w/4));
}

void ExplorerWidget::updateList(QDir& dir) {
    std::cout << "UPDATING EXPLORER" << std::endl;
    this->clear();
    QFileInfoList fileList = dir.entryInfoList();
    for (int i = 0; i < fileList.size(); ++i) {
        QFileInfo info = fileList.at(i);
        if (info.fileName() == "." || info.fileName() == "..")  continue;

        std::cout << info.fileName().toStdString() << std::endl;
        //QTreeWidgetItem *item = new QTreeWidgetItem(this);
        auto sizeCol = 1;
        auto item = new CustomTreeWidgetItem(this, sizeCol);
        item->setIcon(0, provider.icon(info));
        item->setText(0, info.fileName());
        item->setText(sizeCol, fileSizeSI(info.size()));
        item->setText(2, info.lastModified().toString("yyyy.MM.dd - hh:mm:ss"));
    }
}

ExplorerWidget::~ExplorerWidget() {}
