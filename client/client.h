#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
#include<string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/shm.h> 
#include <time.h>
#include<thread>
#include<arpa/inet.h>
class client
{
private:
    int sockfd=0;
    int isbuild=0;
public:
    const char*ip="192.168.137.128";
    const int port=8080;
    client();
    ~client();
    bool myconnect();
    void history();
    bool reg();
    int msend(char*data);
};

