#ifndef TESTPING_H
#define TESTPING_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QtTest>

class TestPing :QObject
{
    Q_OBJECT
public:
    TestPing(QObject *parent = nullptr);
    void startPing();
    void cicloEsperaMensaje();
    QProcess processPing;

public slots:
    void rightMessagePing();

signals:
    void commRecovery();

};

#endif // TESTPING_H
