#ifndef SRBTSERIALDEVICE_H
#define SRBTSERIALDEVICE_H
#include <SoftwareSerial.h>
class SRBTSerialDevice
{
    public:
        /** Default constructor */
        SRBTSerialDevice();
        /** Default destructor */
        virtual ~SRBTSerialDevice();
        String SerialRead(Stream *ser);
        String BTRead(SoftwareSerial *ser);
    protected:
    private:
        String srCommand;
        String btCommand;
};

#endif // SRBTSERIALDEVICE_H
