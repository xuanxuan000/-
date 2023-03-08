#include "widget.h"

#include <QApplication>
#include "qlabel.h"
#include "QGridLayout"
#include "QTimer"
#include "QElapsedTimer"
#include "QThread"
#include "QDebug"
#include "QFile"
#include "QMessageBox"
#include "QProcess"

void mySleep(int ms, bool isSync = false);
const QString CfgFile = "./config.ini";

int main(int argc, char *argv[])
{
    // 清理原程序
    QString cmd;
    cmd = QString("TASKKILL /F /IM %1 /T").arg(argv[0]);
    QProcess p;
    p.start("TASKKILL", QStringList()<< "/F" << "/IM" << argv[0] << "/T");
    p.waitForStarted();
    p.waitForFinished();

    QApplication a(argc, argv);
    QLabel *label = new QLabel("？？？", nullptr);
    label->setStyleSheet("color:green;\
        font-family:'Microsoft YaHei';\
        font-size:28px;");
    label->setAlignment(Qt::AlignCenter);
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(label);
    Widget w;
    w.setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowStaysOnTopHint);
    w.setLayout(layout);
//    w.showFullScreen();

    int showTime = 5, elaspe = 50;
    // 读取配置
    QFile file(CfgFile);
    if(file.open(QIODevice::ReadOnly)){
        QString cfgData = file.readAll().replace("\n", "").replace(" ", "");
        QStringList data = cfgData.split(",");
        if(data.size() != 2){
            QMessageBox::warning(nullptr, "warning", QString("%1 format err").arg(CfgFile));
            return -1;
        }
        showTime = data[0].toInt();
        elaspe = data[1].toInt();
    }else{
        QMessageBox::warning(nullptr, "warning", QString("can not found %1, use default cfg").arg(CfgFile));
    }
    QMessageBox::information(nullptr, "info", QString("show: %1min, elaspe: %2min").arg(showTime).arg(elaspe));

    QTimer *timer = new QTimer();
//    QObject::connect(timer, &QTimer::timeout, &w, &Widget::showFullScreen);
    QObject::connect(timer, &QTimer::timeout, &w, [&](){
        qDebug() << "show";
        w.showFullScreen();
//        mySleep(1000, true);
        mySleep(5*60*1000, true);
        w.hide();
    });
//    timer->start(5*1000);
    timer->start(50*60*1000);

    return a.exec();
}

void mySleep(int ms, bool isSync/* = false*/)
{
    QElapsedTimer timer;
    timer.start();

    while(!timer.hasExpired(ms)) {
        QThread::msleep(1);
        if (isSync) {
            qApp->processEvents();
        }
    }
}
