#include "tree.h"

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

bool Tree::AddElem(Tree * head, QString s)
{
    if (this != head) return false;   //метод можно вызывать только корень дерева

    Tree * temp = this;
    Tree * prev = temp;
    bool found = false;
    while(temp && !found)
    {
        prev = temp;
        if(s == temp->get_ident())
            found = true;
        else if(s < temp->get_ident())
            temp = temp->get_left();
        else if(s > temp->get_ident())
            temp = temp->get_right();
        else return false;
    }

    if(found) return false;           //если элемент с таким индексом уже существует, то добавить новый элемент нельзя

    Tree * newEl = new Tree();
    newEl->set_ident(s);
    newEl->set_left(NULL);
    newEl->set_right(NULL);

    if(s < prev->get_ident())
        prev->set_left(newEl);
    else if(s > prev->get_ident())
        prev->set_right(newEl);
    else return false;

    return true;
}
