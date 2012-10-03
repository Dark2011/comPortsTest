#include <QByteArray>
#include "SerialPort.h"


Serial::Serial(const PortSettings& settings, const QString& name)
: _serial(new QextSerialPort(name, settings, QextSerialBase::EventDriven))
{
    connect(_serial.get(), SIGNAL(readyRead()), this, SLOT(HasData()), Qt::DirectConnection);
}

bool Serial::Open()
{
	return _serial->open(QIODevice::ReadWrite);
}

bool Serial::IsOpened()
{
    return _serial->isOpen();
}

void Serial::Reset()
{};

void Serial::Close()
{
    _serial->close();
}

unsigned Serial::DataAvailable()
{
	return _serial->bytesAvailable();
}

QString Serial::LastError()
{
    return QString(errorCodeToText(_serial->lastError()));
}

QString Serial::Info()
{
    return QString("Serial     \n \
                    Port     %1\n \
                    Baudrate %2\n \
                    Databits %3\n \
                    Stopbits %4\n \
                    Parity   %5\n \
                    Flow     %6\n \
                    ")
                    .arg(_serial->portName())
                    .arg(toArg(_serial->baudRate()))
                    .arg(toArg(_serial->dataBits()))
                    .arg(toArg(_serial->stopBits()))
                    .arg(toArg(_serial->parity()))
                    .arg(toArg(_serial->flowControl()));
}

QByteArray Serial::Receive(unsigned size)
{
    return _serial->read(size);
}

unsigned Serial::Send(const QByteArray& data)
{
    return _serial->write(data);
}

QString errorCodeToText(unsigned errorcode)
{
	switch (errorcode)
	{
		case E_NO_ERROR             : return QString("No Error has occured");
		case E_INVALID_FD           : return QString("Invalid file descriptor (port was not opened correctly)");
		case E_BREAK_CONDITION      : return QString("The port detected a break condition");
		case E_FRAMING_ERROR        : return QString("The port detected a framing error(usually caused by incorrect baud rate settings)");
		case E_IO_ERROR             : return QString("There was an I/O error while communicating with the port");
		case E_BUFFER_OVERRUN       : return QString("Character buffer overrun");
		case E_RECEIVE_OVERFLOW     : return QString("Receive buffer overflow");
		case E_RECEIVE_PARITY_ERROR : return QString("The port detected a parity error in the received data");
		case E_TRANSMIT_OVERFLOW    : return QString("Transmit buffer overflow");
		case E_READ_FAILED          : return QString("General read operation failure");
		case E_WRITE_FAILED         : return QString("General write operation failure");
		
		default						: return QString("Unknown error"); 
	}
}

// UnitsToDigits

int toArg(BaudRateType baudrate)
{
	switch(baudrate)
	{
		case BAUD110    : return CBR_110;             
		case BAUD300    : return CBR_300;             
		case BAUD600    : return CBR_600;             
		case BAUD1200   : return CBR_1200;            
		case BAUD2400   : return CBR_2400;           
		case BAUD4800   : return CBR_4800;            
		case BAUD9600   : return CBR_9600;            
		case BAUD14400  : return CBR_14400;           
		case BAUD19200  : return CBR_19200;           
		case BAUD38400  : return CBR_38400;           
		case BAUD56000  : return CBR_56000;           
		case BAUD57600  : return CBR_57600;        
		case BAUD115200 : return CBR_115200;        
		case BAUD128000 : return CBR_128000;         
		case BAUD256000 : return CBR_256000;

		default			: return CBR_9600;
	}
}

int toArg(DataBitsType databits)
{
	switch (databits)
	{
		case DATA_5 : return 5;
		case DATA_6 : return 6;
		case DATA_7 : return 7;
		case DATA_8 : return 8;

		default		: return 8;
	}
}

int toArg(StopBitsType stopbits)
{
	switch (stopbits)
	{
	    case STOP_1   : return 1;
		case STOP_2   : return 2;

		default		  : return 1;
	}
}

QString toArg(ParityType parity)
{
	switch (parity)
	{
		case PAR_NONE  : return QString("NONE");
		case PAR_ODD   : return QString("ODD");
		case PAR_EVEN  : return QString("EVEN");
		case PAR_MARK  : return QString("MARK");
		case PAR_SPACE : return QString("SPACE");

		default		   : return QString("NONE");
	}
}

QString toArg(FlowType flow)
{
	switch (flow)
	{
		case FLOW_OFF      : return QString("FLOW_OFF");
		case FLOW_HARDWARE : return QString("FLOW_HARDWARE");
		case FLOW_XONXOFF  : return QString("FLOW_XONXOFF");

		default			   : return QString("FLOW_OFF");
	}
}


// DigitsToUnits

BaudRateType BaudRate(int baudrate)
{
	switch(baudrate)
	{
		case CBR_110    : return BAUD110;             
		case CBR_300    : return BAUD300;             
		case CBR_600    : return BAUD600;             
		case CBR_1200   : return BAUD1200;            
		case CBR_2400   : return BAUD2400;           
		case CBR_4800   : return BAUD4800;            
		case CBR_9600   : return BAUD9600;            
		case CBR_14400  : return BAUD14400;           
		case CBR_19200  : return BAUD19200;           
		case CBR_38400  : return BAUD38400;           
		case CBR_56000  : return BAUD56000;           
		case CBR_57600  : return BAUD57600;        
		case CBR_115200 : return BAUD115200;        
		case CBR_128000 : return BAUD128000;         
		case CBR_256000 : return BAUD256000;      

		default			: return BAUD9600;
	}
}

DataBitsType DataBits(int databits)
{
	switch (databits)
	{
		case 5  : return DATA_5;
		case 6  : return DATA_6;
		case 7  : return DATA_7;
		case 8  : return DATA_8;

		default : return DATA_8;
	}
}

StopBitsType StopBits(int stopbits)
{
	switch (stopbits)
	{
	    case 1  : return STOP_1;
		case 2  : return STOP_2;

		default : return STOP_1;
	}
}

ParityType Parity(const QString& parity)
{
	if (parity == "NONE")
		return PAR_NONE;

	if (parity == "ODD")
		return PAR_ODD;
	
	if (parity == "EVEN")
		return PAR_EVEN;
	
	if (parity == "MARK")
		return PAR_MARK;
	
	if (parity == "SPACE")
		return PAR_SPACE;

	return PAR_NONE;
}

FlowType Flow(const QString& flow)
{
	if (flow == "FLOW_OFF")
		return FLOW_OFF;

	if (flow == "FLOW_HARDWARE")
		return FLOW_HARDWARE;
	
	if (flow == "FLOW_XONXOFF")
		return FLOW_XONXOFF;

	return FLOW_OFF;
}