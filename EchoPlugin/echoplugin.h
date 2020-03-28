#ifndef ECHOPLUGIN_H
#define ECHOPLUGIN_H


#include <QObject>
#include <QtPlugin>
#include "echointerface.h"

class EchoPlugin : public QObject, public EchoInterface
{
    Q_OBJECT
    Q_INTERFACES(EchoInterface)
public:
    explicit EchoPlugin(QObject *parent = 0);
    QString echo(const QString &message);
};

#endif // ECHOPLUGIN_H
