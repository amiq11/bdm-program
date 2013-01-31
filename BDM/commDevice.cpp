#include "commDevice.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <stdlib.h>

using namespace std;


#define DEVFILE "/dev/ttyUSB0"
#define BUFSIZE 1000

CommDevice::CommDevice()
{
    this->fd = open( DEVFILE, O_RDWR );
    int count = 0;
    
    while ( this->fd < 0 ) {
        count++;
        perror( "open" );
        if ( count > 10 ) {
            cerr << "Connection Timeout!" << endl;
            exit( -1 );
        }
        sleep( 1 );
        this->fd = open( DEVFILE, O_RDWR );
    }
    cout << "Opened " << DEVFILE << endl;
}

CommDevice::~CommDevice()
{
    close( this->fd );
}

// CommDevice::set()
// {
    
// }

int CommDevice::send( const string &str )
{
    int size = str.size();
    int ret  = write( fd, str.c_str(), size );
    int count = 0;
    
    while ( size > ret && count++ < 10 ) {
        ret += write( fd, str.c_str(), size - ret );
    }

#ifdef _DEBUG_
    cerr << size << " bytes is sent" << endl;
#endif    

    if ( count >= 10 ) return -1;
    return 0;
}

int CommDevice::recv( string &str )
{

    int flags = fcntl( fd, F_GETFL );
    fcntl( fd, F_SETFL, flags | O_NONBLOCK );
    
    char *buf = new char[BUFSIZE];
    int size = 0;
    int tmp = read( fd, buf, BUFSIZE );
    // cout << tmp << endl;
    
    while ( tmp > 0 ) {
        size += tmp;
        tmp = read( fd, buf + size, BUFSIZE - size );
    }
    
    if ( errno != EAGAIN && errno != EWOULDBLOCK ) {
        perror( "read" );
        return -1;
    }

    fcntl( fd, F_SETFL, flags );

#ifdef _DEBUG_
    cout << size << " bytes is received" << endl;
#endif    

    string tmpstr = buf;

    if ( size > 0 ) 
        str = tmpstr.substr( 0, size - 1 );
    else
        str = "";
    
    
    
    return size;
}
