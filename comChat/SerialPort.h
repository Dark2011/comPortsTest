#pragma once
#include <memory>
#include "qextserialport.h"

class Serial
{
//    Q_OBJECT

public:
    Serial(const PortSettings& settings, const QString& name);

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
