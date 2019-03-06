#include "tree.h"

Tree::Tree()
{

}

void Tree::set_hashId(int num)
{
    hashId = num;
}
void Tree::set_ident(QString str)
{
    ident = str;
}
void Tree::set_left(Tree * item)
{
    left = item;
}
void Tree::set_right(Tree * item)
{
    right = item;
}


int Tree::get_hashId()
{
    return hashId;
}
QString Tree::get_ident()
{
    return ident;
}
Tree * Tree::get_left()
{
    return left;
}
Tree * Tree::get_right()
{
    return right;
}

bool Tree::AddElem(Tree * head, QString s, int h)
{
    if (this != head) return false;   //метод можно вызывать только корень дерева

    Tree * temp = this;
    Tree * prev = temp;
    bool found = false;
    while(temp && !found)
    {
        prev = temp;
        if(h == temp->get_hashId())
            found = true;
        else if(h < temp->get_hashId())
            temp = temp->get_left();
        else if(h > temp->get_hashId())
            temp = temp->get_right();
        else return false;
    }

    if(found) return false;           //если элемент с таким индексом уже существует, то добавить новый элемент нельзя

    Tree * newEl = new Tree();
    newEl->set_hashId(h);
    newEl->set_ident(s);
    newEl->set_left(NULL);
    newEl->set_right(NULL);

    if(h < prev->get_hashId())
        prev->set_left(newEl);
    else if(h > prev->get_hashId())
        prev->set_right(newEl);
    else return false;

    return true;
}
