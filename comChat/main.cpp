
#include <QApplication>
#include "SerialPort.h"
#include "myPorts.h"
#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	PortSettings mySet = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 500};

	DataPort transmPort(mySet, "COM1");
	transmPort.openPort();

	DataPort recievePort(mySet, "COM2");
	recievePort.openPort();

	QString data = "StarCraft";
	QByteArray byteArr = data.toAscii();

	transmPort.sendData(byteArr);

	QByteArray temp;
	temp = recievePort.getData();

	transmPort.closePort();
	
	return app.exec();
}
