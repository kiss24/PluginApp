#include "Widget.h"
#include <QtGui>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    createGUI();
    setLayout(layout);
    setWindowTitle("Echo Plugin Example");

    if (!loadPlugin())
    {
        QMessageBox::information(this, "Error", "Could not load the plugin");
        lineEdit->setEnabled(false);
        button->setEnabled(false);
    }
}
void Widget::sendEcho()
{
    QString text = echoInterface->echo(lineEdit->text());
    label->setText(text);
}

void Widget::createGUI()
{
    lineEdit = new QLineEdit;
    label = new QLabel;
    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    button = new QPushButton(tr("Send Message"));

    connect(lineEdit, SIGNAL(editingFinished()),
            this, SLOT(sendEcho()));
    connect(button, SIGNAL(clicked()),
            this, SLOT(sendEcho()));

    layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Message:")), 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(new QLabel(tr("Answer:")), 1, 0);
    layout->addWidget(label, 1, 1);
    layout->addWidget(button, 2, 1, Qt::AlignRight);
    layout->setSizeConstraint(QLayout::SetFixedSize);
}

bool Widget::loadPlugin()
{
    bool ret = true;
    //获取当前应用程序所在路径
    QDir pluginsDir(qApp->applicationDirPath());
    qDebug() << pluginsDir;

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS")
    {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#elif defined(Q_OS_LINUX)
    pluginsDir.cdUp();
#endif
    //切换到插件目录
    pluginsDir.cdUp();
    pluginsDir.cd("plugins");
    qDebug() << pluginsDir;

    //遍历plugins目录下所有文件
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        qDebug() << fileName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));

        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            //插件名称
            QString pluginName = plugin->metaObject()->className();
            //对插件初始化
            if(pluginName == "EchoPlugin")
            {
                echoInterface = qobject_cast<EchoInterface *>(plugin);
                if (echoInterface)
                    ret =  true;
                break;
            }
            else
            {
                ret = false;
            }
        }
    }
    return ret;
}

Widget::~Widget()
{

}
