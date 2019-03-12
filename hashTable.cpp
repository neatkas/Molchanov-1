#include "hashTable.h"
#include "hashFun.h"

HashTable::HashTable()
{

}

void HashTable::set_N(int num)
{
    N = num;
}

void HashTable::set_masStrItem(int i, QString s)
{
    masStr[i] = s;
}

int HashTable::get_N()
{
    return N;
}

QString HashTable::get_masStrItem(int i)
{
    return masStr[i];
}

void HashTable::Create(QStringList m)
{
    set_N(250);             //максимальное количество идентификаторов

    for(int i=0; i < get_N(); i++)
    {
        masStr.append("");
    }

    foreach(QString str, m)
    {
        int h = HashFun(str);

        if(h > get_N())
            h = h % get_N();

        if(masStr[h] != "")
        {
            int i = 1;
            int hi = -1;
            while(hi != h)
            {
                hi = (h+i) % get_N();
                if(masStr[hi] == "")
                    break;
                i++;
            }
            if(hi != h) h = hi;
            else h = -1;
        }

        if(h != -1)
        {
            set_masStrItem(h, str);
        }
    }
}

bool HashTable::Find(QString s, int &s_count, int &s_hash)
{
    s_count++;
    s_hash = 0;

    int hi = -1;
    int i = 1;

    int h = HashFun(s);

    if(h < get_N())
    {
        s_hash++;
        if(masStr[h] == "")
        {
            return false;
        }

        if(masStr[h] == s)
        {
            return true;
        }
    }

    while (hi != h)
    {
        s_hash++;
        hi = (h + i) % get_N();

        if(hi == h || masStr[hi] == "")
        {
            return false;
        }

        if(masStr[hi] == s)
        {
            return true;
        }
        i++;
    }

    //запись в массив статистики

    return false;
}

bool HashTable::FindAll(QStringList list, int &s_count, int &s_hash, int &s_hashAll)
{
    s_hashAll = 0;
    bool result = false;

    foreach(QString item, list)
    {
        result = Find(item, s_count, s_hash);
        s_hashAll += s_hash;
    }

    return result;
}
