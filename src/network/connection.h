/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QByteArray>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>

static const int MaxBufferSize = 1024000;

class Connection : public QTcpSocket
{
  CS_OBJECT(Connection)

  public:
    enum ConnectionState {
        WaitingForGreeting,
        ReadingGreeting,
        ReadyForUse
    };

    enum DataType {
        PlainText,
        Ping,
        Pong,
        Greeting,
        Undefined
    };

    Connection(QObject *parent = nullptr);

    QString name() const;
    void setGreetingMessage(const QString &message);
    bool sendMessage(const QString &message);

    CS_SIGNAL_1(Public, void readyForUse())
    CS_SIGNAL_2(readyForUse)

    CS_SIGNAL_1(Public, void newMessage(const QString &from, const QString &message))
    CS_SIGNAL_2(newMessage, from, message)

 protected:
    void timerEvent(QTimerEvent *timerEvent) override;

 private:
    int readDataIntoBuffer(int maxSize = MaxBufferSize);
    int dataLengthForCurrentDataType();
    bool readProtocolHeader();
    bool hasEnoughData();
    void processData();

    // slots
    void processReadyRead();
    void sendPing();
    void sendGreetingMessage();

    QString greetingMessage;
    QString username;
    QTimer pingTimer;
    QTime pongTime;
    QByteArray buffer;
    ConnectionState state;
    DataType currentDataType;
    int numBytesForCurrentDataType;
    int transferTimerId;
    bool isGreetingMessageSent;
};

#endif
