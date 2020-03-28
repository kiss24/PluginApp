#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "echointerface.h"

QT_BEGIN_NAMESPACE
class QString;
class QLineEdit;
class QLabel;
class QPushButton;
class QGridLayout;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void sendEcho();

private:
    void createGUI();
    //¼ÓÔØ²å¼þ
    bool loadPlugin();

    EchoInterface *echoInterface;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *button;
    QGridLayout *layout;
};

#endif // WIDGET_H
