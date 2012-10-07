
#include <QApplication>
#include "SerialPort.h"
#include "myPorts.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	PortSettings mySet = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 500};

	DataPort transmPort(mySet, "COM1");
	transmPort.port->Open();

	DataPort recievePort(mySet, "COM2");
	recievePort.port->Open();


	QString data = "StarCraf";
	QByteArray byteArr = data.toAscii();
	transmPort.port->Send(byteArr);

	QByteArray temp;
	temp = recievePort.recData;
	

	transmPort.port->Close();
	
	return app.exec();
}
