#pragma once
#include "SerialPort.h"
#include <QtGui>

class DataPort : QDialog
{
	Q_OBJECT

public: 
	DataPort(PortSettings& settings, const QString &name, QWidget *parent = 0) : QDialog(parent), portSet(settings)
	{
		port = new Serial(portSet, name);
		recData = NULL;
		connect(port, SIGNAL(readyRead()), this, SLOT(readData()));
	}

	public slots:
		void readData()
		{
		    unsigned availableData = port->DataAvailable();
			recData = port->Receive(availableData);
			port->Close();
		}
public:	
	PortSettings portSet;
	Serial* port;
	QByteArray recData;
};
