#include "client.h"
client::client()
{
}
client::~client()
{
    if (isbuild == 1)
    {
        close(sockfd);
    }
}
bool client::reg()
{
    char *id;
    std::cout << "ÇëÊäÈë×¢²áid£º " << std::endl;
    std::cin >> id;
    int tmp = 0;
    tmp = send(sockfd, id, strlen(id), 0);
    return tmp;
}
int client::msend(char *data)
{
    send(sockfd, data, strlen(data), 0);
}
void client::history(){};
bool client::myconnect()
{
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    inet_pton(PF_INET, ip, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("connection failed\n");
        return false;
    }
    else
    {
        printf("connection succeed");
        isbuild = 1;
        return true;
    }
}
