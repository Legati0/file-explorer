#include "customtreewidgetitem.h"
#include <iostream>

CustomTreeWidgetItem::CustomTreeWidgetItem(QTreeWidget* parent, int sizeCol) : QTreeWidgetItem(parent), sizeCol(sizeCol)
{

}
bool CustomTreeWidgetItem::operator<(const QTreeWidgetItem& other) const {
    int column = treeWidget()->sortColumn();
    if (column == sizeCol) {
        QString sizes("kMGTPEZY");
        auto thisTxt = text(column);
        int thisIndex = thisTxt.indexOf(' ');
        double thisVal = thisTxt.midRef(0, thisIndex).toDouble();
        QChar thisSize = thisTxt.at(thisIndex  + 1);
        auto otherTxt = other.text(column);
        int otherIndex = otherTxt.indexOf(' ');
        double otherVal = otherTxt.midRef(0, otherIndex).toDouble();
        QChar otherSize = otherTxt.at(otherIndex  + 1);

        auto thisSizeIndex = sizes.indexOf(thisSize);
        auto otherSizeIndex = sizes.indexOf(otherSize);
        if (thisSizeIndex != otherSizeIndex)
            return thisSizeIndex < otherSizeIndex;
        return thisVal < otherVal;
    }
    return QTreeWidgetItem::operator<(other);
}
