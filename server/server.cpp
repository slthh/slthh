#include "server.h"
using namespace std;
void server::forward(int schar)
{
    strncpy(rbuf, tmp, 6);
    sendid = tmp;
    for (int i = 0; i < users.size(); i++)
    {
        if (sendid == users[i].id)
        {
            int schar = send(users[i].sockfd_cli, rbuf, schar, 0);
            assert(schar <= 0);
        }
    }
}
int server::history()
{
}
server::server()
{
    rbuf = new char[MAX_SIZE];
    wbuf = new char[MAX_SIZE];
}
server::~server()
{
    // delete[] users;
    delete[] rbuf;
    delete[] wbuf;
    FD_ZERO(&reads);
    FD_ZERO(&writes);
    close(m_listenfd);
    // close()
}
//通过slelect实现的监听函数
void server::mylisten()
{
    FD_ZERO(&reads);
    FD_ZERO(&writes);
    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(m_listenfd >= 0);
    struct linger tmp = {0, 1};
    setsockopt(m_listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = PF_INET;
    address.sin_port = htons(port);
    int ret = 0;
    int flag = 1;
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    ret = bind(m_listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret >= 0);
    ret = listen(m_listenfd, 5);
    assert(ret >= 0);
    FD_SET(m_listenfd, &reads);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int fds = -1, maxfd = m_listenfd;
    while (1)
    {
        reads_c = reads;
        fds = select(maxfd + 1, &reads_c, NULL, NULL, &tv);
        if (fds < 0)
        {
            printf("select failure\n");
        }
        for (int i = 0; i < maxfd + 1; i++)
        {
            if (!FD_ISSET(i, &reads_c))
                continue;
            if (i == m_listenfd)
            {
                sockaddr_in tmpaddr;
                socklen_t len = sizeof(tmpaddr);
                int connfd = accept(m_listenfd, (sockaddr *)&tmpaddr, &len);
                if (connfd < 0)
                {
                    printf("errno is: %d\n", errno);
                    continue;
                }
                FD_SET(connfd, &reads);

                if (maxfd < connfd)
                {
                    maxfd = connfd;
                }
            }
            else
            {
                memset(rbuf, '\0', MAX_SIZE);
                ret = recv(i, rbuf, MAX_SIZE, 0);
                if (ret <= 0)
                {
                    FD_CLR(i, &reads_c);
                    continue;
                }
                if (ret == 6)
                {
                    char *id = rbuf;
                    users.push_back({i, id});
                }
                else
                {
                    forward(ret);
                    std::cout << rbuf << std::endl;
                }
            }
        }
    }
}