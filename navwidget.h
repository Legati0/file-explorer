#ifndef NAVWIDGET_H
#define NAVWIDGET_H

#include <QWidget>
#include <QDir>
#include <QLineEdit>
#include <QPushButton>


class NavWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* edit;
    QPushButton* up;
    QPushButton* back;
    QPushButton* forward;
    QPushButton* newDir;
public:
    NavWidget(QWidget* parent=nullptr);
    virtual ~NavWidget();
    void updateText(QString txt);
    QLineEdit* getEdit();
    QPushButton* getUpBtn();
    QPushButton* getBackBtn();
    QPushButton* getForwardBtn();
    QPushButton* getMkdirBtn();

signals:

};

#endif // NAVWIDGET_H
