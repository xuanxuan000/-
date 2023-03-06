#include "widget.h"

#include <QApplication>
#include "qlabel.h"
#include "QGridLayout"
#include "QTimer"
#include "QElapsedTimer"
#include "QThread"
#include "qDebug"

void mySleep(int ms, bool isSync = false);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel *label = new QLabel("起来走走，去喝点儿水。", nullptr);
    label->setStyleSheet("color:green;\
        font-family:'Microsoft YaHei';\
        font-size:18px;");
    label->setAlignment(Qt::AlignCenter);
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(label);
    Widget w;
    w.setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowStaysOnTopHint);
    w.setLayout(layout);
//    w.showFullScreen();

    QTimer *timer = new QTimer();
//    QObject::connect(timer, &QTimer::timeout, &w, &Widget::showFullScreen);
    QObject::connect(timer, &QTimer::timeout, &w, [&](){
        qDebug() << "show";
        w.showFullScreen();
//        mySleep(1000, true);
        mySleep(3*60*1000, true);
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
