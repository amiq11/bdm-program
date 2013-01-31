#ifndef _COMMANDMANAGER_H_
#define _COMMANDMANAGER_H_

#include <QObject>
#include <QThread>
#include <QMutex>

typedef struct 
{
    int length;
    int angle;
} command_t;

class CommandManager : public QThread
{
    Q_OBJECT

public:
    CommandManager();
    ~CommandManager();
    void setCommand( int length, int angle );
    void run();
private:
    std::vector<command_t *> commands;
    QMutex mutex;
};
    
#endif
