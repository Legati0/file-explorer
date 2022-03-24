#include "renamedialog.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QPushButton>
#include <iostream>

RenameDialog::RenameDialog(QWidget *parent)
    : QDialog{parent}
{
    this->setModal(true);
    this->setWindowTitle("Rename");

    auto hLayout = new QHBoxLayout(this);
    iconLbl = new QLabel();
    //iconLbl->setPixmap(provider.icon(QFileInfo(QString("asd.py"))).pixmap(QSize(64, 64)));
    hLayout->addWidget(iconLbl);

    auto vLayout = new QVBoxLayout();
    vLayout->addWidget(new QLabel("Enter a new name"));
    edit = new QLineEdit();
    vLayout->addWidget(edit);

    auto btnLayout = new QHBoxLayout();
    auto renameBtn = new QPushButton("Rename");
    btnLayout->addWidget(renameBtn);
    auto cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(cancelBtn);
    //renameBtn->setFocus();

    vLayout->addLayout(btnLayout);

    hLayout->addLayout(vLayout);

    connect(renameBtn, &QPushButton::clicked, this, &RenameDialog::rename);
    connect(cancelBtn, &QPushButton::clicked, this, &RenameDialog::cancel);
}

void RenameDialog::setFile(QString fname) {
    // TODO handle dir icon
    edit->setText(fname);
    iconLbl->setPixmap(provider.icon(QFileInfo(fname)).pixmap(QSize(64, 64)));
    if (fname.contains('.'))
        edit->setSelection(0, fname.lastIndexOf('.'));
    else
        edit->selectAll();
}
void RenameDialog::cancel() {
    this->canceled = true;
    this->close();
}
void RenameDialog::rename() {
    if (text().isEmpty()) {
        edit->setStyleSheet("background: #8AFB0000");
        return;
    }
    this->canceled = false;
    this->close();
}
bool RenameDialog::isCanceled() const {
    return canceled;
}
QString RenameDialog::text() const {
    return edit->text();
}
RenameDialog::~RenameDialog() {}
