/**
 * @author Daniel Schreiner
 * @email schreiner.daniel@gmail.com
 */
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
        /** Read data from COM PORT
            returns String
        */
        String SerialRead(Stream *ser);
        /** Read data from Bluetooth
            returns String
        */

        String BTRead(SoftwareSerial *ser);
    protected:
    private:
        String srCommand;
        String btCommand;
};

#endif // SRBTSERIALDEVICE_H
