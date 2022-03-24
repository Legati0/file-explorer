#ifndef CUSTOMTREEWIDGETITEM_H
#define CUSTOMTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>

class CustomTreeWidgetItem : public QTreeWidgetItem
{
private:
    int sizeCol;
    bool operator<(const QTreeWidgetItem& other) const;
public:
    CustomTreeWidgetItem(QTreeWidget* parent=nullptr, int sizeCol=-1);
};

#endif // CUSTOMTREEWIDGETITEM_H
