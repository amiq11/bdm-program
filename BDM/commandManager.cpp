#include "commandManager.h"
#include <iostream>

using namespace std;


CommandManager::CommandManager()
{

}

CommandManager::~CommandManager()
{

}

void CommandManager::setCommand( int length, int angle )
{
    command_t *tmp = new command_t;
    tmp->length = length * cos( (double)angle * 2 * M_PI / 360.0 );
    tmp->angle  = 0;
    if ( tmp->length < 0 ) {
        tmp->length = -tmp->length;
        tmp->angle += 180;
    }
    mutex.lock();
    commands.push_back( tmp );
    mutex.unlock();

    tmp = new command_t;
    tmp->length = length * sin( (double)angle * 2 * M_PI / 360.0 );
    tmp->angle  = 90;
    if ( tmp->length < 0 ) {
        tmp->length = -tmp->length;
        tmp->angle += 180;
    }

    mutex.lock();
    commands.push_back( tmp );
    mutex.unlock();
    
}

void CommandManager::run()
{
    mutex.lock();
    vector < command_t * > data( commands.size() );
    copy( commands.begin(), commands.end(), data.begin() );
    mutex.unlock();
    
    vector < command_t * > ::iterator it = data.begin();
    for ( ; it < data.end(); it++ ) {
        cout << "len,angle = " << (*it)->length << ", " << (*it)->angle << endl;
    }
}
