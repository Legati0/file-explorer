#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QFileIconProvider>
#include <QLineEdit>
#include <QLabel>

class RenameDialog : public QDialog
{
    Q_OBJECT
private:
    bool canceled = false;
    QFileIconProvider provider;
    QLineEdit* edit;
    QLabel* iconLbl;
    void cancel();
    void rename();
public:
    RenameDialog(QWidget *parent = nullptr);
    virtual ~RenameDialog();

    void setFile(QString fname);
    bool isCanceled() const;
    QString text() const;

signals:

};

#endif // RENAMEDIALOG_H
