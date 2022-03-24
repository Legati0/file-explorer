#ifndef MKDIRDIALOG_H
#define MKDIRDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>

class MkdirDialog : public QDialog
{
    Q_OBJECT
private:
    bool canceled = false;
    QLineEdit* edit;
    void cancel();
    void create();
public:
    MkdirDialog(QWidget *parent = nullptr);
    virtual ~MkdirDialog();

    bool isCanceled() const;
    QString text() const;

signals:

};

#endif // MKDIRDIALOG_H
