//#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <string.h>
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
#include <thread>
#include <sys/select.h>
static const int max_cli = 100;
const int MAX_SIZE = 1024;
struct client
{
    int sockfd_cli;
    char *id;
};

class server
{
private:
    int port = 8080;
    std::vector<client> users;
    int m_listenfd;
    fd_set reads, writes, reads_c, writes_c;
    char *rbuf, *wbuf;
    char tmp[6];
    char *sendid, recvid;

public:
    server();
    ~server();
    void mylisten();
    void forward(int schar);
    int history();
};
