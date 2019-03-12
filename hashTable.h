#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QMainWindow>
#include <QString>

class HashTable
{
private:
    int N;
    QStringList masStr;
public:
    HashTable();

    void set_N(int num);
    void set_masStrItem(int i, QString s);

    int get_N();
    QString get_masStrItem(int i);

    void Create(QStringList m);
    bool Find(QString s, int &s_count, int &s_hash);    //возвращает массив с данными о результатах поиска и собранную статистику
    bool FindAll(QStringList list,int &s_count, int &s_hash, int &s_hashAll);          //возвращает массив с данными о результатах поиска и собранную статистику
};

#endif // HASHTABLE_H
