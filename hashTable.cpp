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
    set_min(HashFun("0"));
    set_max(HashFun("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"));
    set_N(250);             //максимальное количество идентификаторов

    for(int i=0; i < get_N(); i++)
    {
        masStr.append("");
    }

    int i = 0;
    foreach(QString str, m)
    {
        int h = HashFun(str);

        /*
        if(h < get_min() || h > get_max())
            continue;
        */


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

        //если это не так - процедура рехэширования
        if(rehash)
        {
            int j = 1;
            int hi = -1;
            while(hi != (h % get_N()))
            {
                hi = (h+j) % get_N();   //рехэширование

                rehash = false;
                foreach(QString str_num, mas)
                {
                    if(str_num.toInt() == hi)
                    {
                        rehash = true;          //true - что-то пошло не так
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

QStringList HashTable::Find(QString s, int &s_count)
{
    s_count++;

    QStringList result;
    bool rehashed;

    result.append("false");

    int h = HashFun(s);

    if(h <= get_N()) rehashed = true;
    else rehashed = false;

    if(!rehashed)
    {
        int hi = -1;
        int i = 1;
        while ( (h % get_N())!= hi && !rehashed)
        {
            hi = (h + i) % get_N();
            foreach(QString str_num, mas)
            {
                if(str_num.toInt() == hi)
                {
                    if(s == get_masStrItem(hi))
                    {
                        rehashed = true;
                        result.append(s);
                    }
                    break;
                }
            }
            i++;
        }
    }

    if(rehashed) result[0] = "true";

    //запись в массив статистики

    return result;
}

QStringList HashTable::FindAll(int &s_count)
{
    QStringList result;

    result.append("true");

    foreach(QString item, masStr)
    {
        QStringList temp;
        temp.append(Find(item, s_count));

        //добавить - обработка переданной статистики

        //если что-то пошло не так - заменить true в первом элементе result на false
        if(temp[0] != "true")
        {
            result[0] = "false";
        }
    }

    return result;
}
