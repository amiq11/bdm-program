#ifndef COMM_DEVICE_H
#define COMM_DEVICE_H

#include <string>

class CommDevice
{
public:
    CommDevice();
    ~CommDevice();
    // int  set();
    int  send( const std::string &str );
    int  recv( std::string &str );
private:
    int fd;
};
#endif /* Not def: COMM_DEVICE_H */
