#include "myPorts.h"

DataPort::DataPort(PortSettings& settings, const QString &name, QWidget *parent) : QObject(parent), portSet(settings)
{
	port = new Serial(portSet, name);
	recData = NULL;
	connect(port, SIGNAL(readyRead()), this, SLOT(readData()));
}

void DataPort::sendData(QByteArray& data)
{
	port->Send(data);
}

void DataPort::openPort()
{
	port->Open();
}

void DataPort::closePort()
{
	port->Close();
}

const QByteArray& DataPort::getData()const
{
	return recData;
}



void DataPort::readData()
{
	if(!port->IsOpened())
	  port->Open();

	unsigned availableData = port->DataAvailable();
	recData = port->Receive(availableData);
	port->Close();
}