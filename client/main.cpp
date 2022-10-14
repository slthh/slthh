#include "client.h"
#include <memory>
#include <thread>
using namespace std;
int main()
{
    int count = 0;
    auto myclient = make_shared<client>();
    if (!myclient->myconnect() && myclient->reg())
    {
        cout << "please restart" << endl;
    }
    else
    {
        while (true)
        {

            char *information = NULL;
            cout << "输入消息" << endl;
            cin >> information;
            myclient->msend(information);
        }
    }

    return 0;
}
