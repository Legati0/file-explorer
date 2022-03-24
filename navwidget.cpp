#include "mainwindow.h"
#include "navwidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>


NavWidget::NavWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    up = new QPushButton("^");
    up->setMaximumWidth(40);
    back = new QPushButton("<");
    back->setMaximumWidth(40);
    forward = new QPushButton(">");
    forward->setMaximumWidth(40);
    edit = new QLineEdit();
    newDir = new QPushButton("+");
    newDir->setMaximumWidth(40);

    layout->addWidget(back);
    layout->addWidget(forward);
    layout->addWidget(up);
    layout->addWidget(edit);
    layout->addWidget(newDir);

}

void NavWidget::updateText(QString txt) {
    edit->setText(txt);
}
QLineEdit* NavWidget::getEdit() {
    return edit;
}
QPushButton* NavWidget::getUpBtn() {
    return up;
}
QPushButton* NavWidget::getBackBtn() {
    return back;
}
QPushButton* NavWidget::getForwardBtn() {
    return forward;
}
QPushButton*  NavWidget::getMkdirBtn() {
    return newDir;
}


NavWidget::~NavWidget() {}
