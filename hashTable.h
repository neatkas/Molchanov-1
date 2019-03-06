#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QMainWindow>
#include <QString>

class HashTable
{
private:
    int N;
    int min;
    int max;
    QStringList mas;
    QStringList masStr;
public:
    HashTable();

    void set_N(int num);
    void set_min(int num);
    void set_max(int num);
    void set_masItem(int num);
    void set_masStrItem(int i, QString s);

    int get_N();
    int get_min();
    int get_max();
    int get_masItem(int i);
    QString get_masStrItem(int i);

    void Create(QStringList m);
    QStringList Find(QString s, int &s_count);    //возвращает массив с данными о результатах поиска и собранную статистику
    QStringList FindAll(int &s_count);          //возвращает массив с данными о результатах поиска и собранную статистику
};

#endif // HASHTABLE_H
