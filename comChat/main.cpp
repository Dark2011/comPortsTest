
#include <QtCore/QCoreApplication>
#include "SerialPort.h"
#include "myPorts.h"


int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	PortSettings mySet = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 500};

	DataPort transmPort(mySet, "COM10");
	transmPort.port->Open();

	DataPort recievePort(mySet, "COM11");
	recievePort.port->Open();
	

	QString data = "StarCraft";
	QByteArray byteArr = data.toAscii();
	transmPort.port->Send(byteArr);

	return app.exec();
}
