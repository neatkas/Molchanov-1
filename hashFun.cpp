#include "hashFun.h"

int HashFun(QString str)
{
    int h=0;

    for(int i=0; i < str.length(); i++)
    {
        h += str[i].unicode() % 250;
    }

    return h;
}
