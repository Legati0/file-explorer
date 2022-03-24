#include "mkdirdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <iostream>

MkdirDialog::MkdirDialog(QWidget *parent)
    : QDialog{parent}
{
    this->setModal(true);
    this->setWindowTitle("New Dir");

    auto vLayout = new QVBoxLayout(this);
    auto lbl = new QLabel("Enter a name for the new dir");
    edit = new QLineEdit();
    vLayout->addWidget(lbl);
    vLayout->addWidget(edit);
    auto btnLayout = new QHBoxLayout();
    auto createBtn = new QPushButton("Create");
    btnLayout->addWidget(createBtn);
    auto cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(cancelBtn);

    vLayout->addLayout(btnLayout);

    connect(createBtn, &QPushButton::clicked, this, &MkdirDialog::create);
    connect(cancelBtn, &QPushButton::clicked, this, &MkdirDialog::cancel);
}
void MkdirDialog::cancel() {
    this->canceled = true;
    this->close();
}
void MkdirDialog::create() {
    if (text().isEmpty()) {
        edit->setStyleSheet("background: #8AFB0000");
        return;
    }
    this->canceled = false;
    this->close();
}

bool MkdirDialog::isCanceled() const {
    return canceled;
}
QString MkdirDialog::text() const {
    return edit->text();
}
MkdirDialog::~MkdirDialog() {}
