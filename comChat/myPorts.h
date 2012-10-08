#pragma once
#include "SerialPort.h"
#include <QtGui>

class DataPort : public QObject
{
	Q_OBJECT

public: 
	DataPort(PortSettings& settings, const QString &name, QWidget *parent = 0);
    void sendData(QByteArray &data);
	void openPort();
	void closePort();
	const QByteArray& getData()const;

private slots:
	void readData();
		 
private:	
	PortSettings portSet;
	Serial* port;
	QByteArray recData;
};
