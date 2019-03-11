#include "hashTable.h"
#include "hashFun.h"

HashTable::HashTable()
{

}

void HashTable::set_N(int num)
{
    N = num;
}
void HashTable::set_min(int num)
{
    min = num;
}
void HashTable::set_max(int num)
{
    max = num;
}
void HashTable::set_masItem(int num)
{
    mas.append(QString::number(num));
}
void HashTable::set_masStrItem(int i, QString s)
{
    masStr[i] = s;
}

int HashTable::get_N()
{
    return N;
}
int HashTable::get_min()
{
    return min;
}
int HashTable::get_max()
{
    return max;
}
int HashTable::get_masItem(int i)
{
    return mas[i].toInt();
}
QString HashTable::get_masStrItem(int i)
{
    return masStr[i];
}

void HashTable::Create(QStringList m)
{
    //set_min(HashFun("0"));
    //set_max(HashFun("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"));
    set_N(250);             //максимальное количество идентификаторов

    for(int i=0; i < get_N(); i++)
    {
        masStr.append("");
    }

    int i = 0;
    foreach(QString str, m)
    {
        int h = HashFun(str);

        //проверить, что идентификатора с таким индексом еще нет
        bool rehash = false;         //true - требуется рехэширование
        foreach(QString str_num, mas)
        {
            if(str_num.toInt() == h)
            {
                rehash = true;
                break;
            }
        }

        //проверка выхода за пределы массива
        if(h > get_N()) rehash = true;

        //процедура рехэширования
        if(rehash)
        {
            int j = 1;
            int hi = -1;
            while(hi != h)
            {
                hi = (h+j) % get_N();   //рехэширование

                rehash = false;
                foreach(QString str_num, mas)
                {
                    if(str_num.toInt() == hi)
                    {
                        rehash = true;          //true - ячейка, на которую указывает hi, уже занята
                        break;
                    }
                }

                if(!rehash) break;
                j++;
            }
            if(hi == h) rehash = true;
            if(!rehash) h = hi; //если rehash = false - рехэширование помогло, иначе - добавить элемент нельзя, рехэшируем дальше
        }

        if(!rehash)
        {
            set_masItem(h);
            set_masStrItem(h, str);
        }
        i++;
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
