#include "echoplugin.h"

EchoPlugin::EchoPlugin(QObject *parent) :
    QObject(parent)
{
}

QString EchoPlugin::echo(const QString &message)
{
    return message;
}

Q_EXPORT_PLUGIN2(EchoPlugin, EchoPlugin)
