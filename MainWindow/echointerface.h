#ifndef ECHOINTERFACE_H
#define ECHOINTERFACE_H

#include <QString>

class EchoInterface
{
public:
    virtual ~EchoInterface() {}
    virtual QString echo(const QString &message) = 0;
};

#define EchoInterface_lib "Example.Plugin.EchoInterface"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(EchoInterface, EchoInterface_lib)
QT_END_NAMESPACE

#endif // ECHOINTERFACE_H
