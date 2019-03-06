#ifndef TREE_H
#define TREE_H

#include <QMainWindow>


class Tree
{
private:
    int hashId;
    QString ident;
    Tree * left;
    Tree * right;
public:
    Tree();
    void set_hashId(int num);
    void set_ident(QString str);
    void set_left(Tree * item);
    void set_right(Tree * item);

    int get_hashId();
    QString get_ident();
    Tree * get_left();
    Tree * get_right();

    bool AddElem(Tree * head, QString s, int h);
};

#endif // TREE_H
