#pragma once
#include <memory>
#include <QtGui/QWidget>
#include "qextserialport.h"

class Serial : public QObject
{
  Q_OBJECT

public:
    Serial(const PortSettings& settings, const QString& name, QWidget *parent = 0);

public:
    virtual bool       Open();
    virtual bool       IsOpened();
    virtual void       Reset();
    virtual void       Close();

    virtual unsigned   DataAvailable();
    virtual QString    LastError();
    virtual QString    Info();

    virtual QByteArray Receive(unsigned size);
    virtual unsigned   Send(const QByteArray& data); 

signals:
	void readyRead();

private:
    typedef std::tr1::shared_ptr<QextSerialPort> SerialPtr;
    SerialPtr _serial;
};

QString errorCodeToText(unsigned errorcode);

// UnitsToDigits
int toArg(BaudRateType baudrate);
int toArg(DataBitsType databits);
int toArg(StopBitsType stopbits);
QString toArg(FlowType flowcontrol);
QString toArg(ParityType parity);

// DigitsToUnits
BaudRateType BaudRate(int baudrate);
DataBitsType DataBits(int databits);
StopBitsType StopBits(int stopbits);
FlowType     Flow    (const QString& flow);
ParityType   Parity  (const QString& parity);
