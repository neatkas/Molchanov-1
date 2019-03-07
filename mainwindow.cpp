#include "mainwindow.h"
#include "tree.h"
#include "hashTable.h"
#include "hashFun.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QTextStream>
#include <QString>


QString static pathToFile;
QStringList static identList;

int static search_count = 0;
int static search_tree = 0;
int static search_treeAll = 0;
int static search_hash = 0;
int static search_hashAll = 0;


Tree static * head = NULL;
HashTable static hTable;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()   //(***********************************************)
{
    //DeleteTree();

    delete ui;
}

void MainWindow::on_pushButton_clicked()     //кнопка "Выбрать файл"
{
       pathToFile = QFileDialog::getOpenFileName(0, "OpenDialog", "", "*.txt");
       ui->lineEdit_fileName->setText(pathToFile);
}

void MainWindow::on_pushButton_6_clicked()   //кнопка "Выход из программы"
{
    //надо освободить выделенную память или здесь, или в деструкторе главного класса (**..*)
    DeleteTree(head);

    //this->close();
    qApp->quit();
}

void MainWindow::on_pushButton_2_clicked()   //кнопка "Загрузить файл"
{    
    if(ui->lineEdit_fileName->text() == "") return;

    QFile file(pathToFile);
    bool opened = 1;
    if (!file.open(QFile::ReadOnly))
    {
        opened = 0;
        QMessageBox::warning(this, tr("Application"), tr("Cannot open file %1:\n%2.").arg(pathToFile));
        return;
    }


    //перед загрузкой данных нужно удалить все элементы из поля
    //ui->listWidget->clear();


    while(!file.atEnd())
    {
        identList.append(file.readLine().trimmed());
    }

    ui->listWidget->addItems(identList);

    if(opened)
    {
        CreateTree();
        CreateHash();
    }

    if(opened) file.close();

    ui->tree->setText("");
    ShowTree(head, 0);
}

void MainWindow::on_pushButton_4_clicked()   //кнопка "Сброс"
{
    ui->lineEdit_ident->setText("");
    search_count = 0;
    search_tree = 0;
    search_treeAll = 0;
    search_hash = 0;
    search_hashAll = 0;
    ui->label_count->setText("");
    ui->label_14->setText("Идентификатор");
    ui->label_24->setText("Идентификатор");
    ui->label_compare_1->setText("");
    ui->label_compare_2->setText("");
    ui->label_compareAll_1->setText("");
    ui->label_compareAll_2->setText("");
    ui->label_compareAvr_1->setText("");
    ui->label_compareAvr_2->setText("");
}

void MainWindow::on_pushButton_3_clicked()   //кнопка "Поиск"
{
    if(ui->lineEdit_ident->text() == "" || identList.length() == 0) return;

    search_tree = 0;
    search_hash = 0;
    search_treeAll = 0;
    search_hashAll = 0;

    if(ui->lineEdit_ident->text() != "")
    {
        findTree(ui->lineEdit_ident->text(), search_count, search_tree);
        findHash(ui->lineEdit_ident->text(), search_count, search_hash);
    }
    else
    {
        //вывести ошибку - Введите идентификатор!
    }
    search_treeAll = search_tree;
    search_hashAll = search_hash;

    ui->label_count->setText(QString::number(search_count));
    ui->label_compare_2->setText(QString::number(search_tree));
    ui->label_compareAll_2->setText(QString::number(search_treeAll));
    ui->label_compareAvr_2->setText(QString::number(search_tree/search_treeAll));

    ui->label_compare_1->setText(QString::number(search_hash));
    ui->label_compareAll_1->setText(QString::number(search_hashAll));
    ui->label_compareAvr_1->setText(QString::number(search_hash/search_hashAll));
}

void MainWindow::on_pushButton_5_clicked()   //кнопка "Найти все"
{
    findTreeAll(identList, head, search_count, search_tree, search_treeAll);
    findHashAll(identList, search_count, search_hash, search_hashAll);
    ui->label_count->setText(QString::number(search_count));

    ui->label_compare_2->setText(QString::number(search_tree));
    ui->label_compareAll_2->setText(QString::number(search_treeAll));

    ui->label_compareAvr_2->setText(QString::number((double)search_treeAll/(double)identList.length(), 'f', 3));

    ui->label_compare_1->setText(QString::number(search_hash));
    ui->label_compareAll_1->setText(QString::number(search_hashAll));

    ui->label_compareAvr_1->setText(QString::number((double)search_hashAll/(double)identList.length(), 'f', 3));
}


void MainWindow::CreateTree()
{
    head = new Tree();
    head->set_hashId( HashFun(identList[0]) );
    head->set_ident(identList[0]);
    head->set_left(NULL);
    head->set_right(NULL);

    foreach(QString s, identList)
    {
        if(!head->AddElem(head, s, HashFun(s)))
            ;//сообщить, с каким идентификатором возникли проблемы
    }
}

void MainWindow::CreateHash()
{
    hTable.Create(identList);
}


bool MainWindow::findTree(QString str, int &s_count, int &s_tree)
{
    //алгоритм поиска номер 1 - бинарное дерево

    s_count++;
    s_tree = 0;

    int h = HashFun(str);

    Tree * temp = head;
    bool found = false;

    while(temp && !found)
    {
        s_tree++;
        if(h == temp->get_hashId())
            found = true;
        else if(h < temp->get_hashId())
            temp = temp->get_left();
        else if(h > temp->get_hashId())
            temp = temp->get_right();
        else return false;
    }

    if(found)
    {
        ui->label_24->setText(trUtf8("Идентификатор найден"));
        return true;
    }
    else
    {
        ui->label_24->setText(trUtf8("Идентификатор не найден"));
        return false;
    }
}

void MainWindow::findTreeAll(QStringList list, Tree * item, int &s_count, int &s_tree, int &s_treeAll)
{
    foreach(QString str, list)
    {
        findTree(str, s_count, s_tree);
        s_treeAll += s_tree;
    }
    /*if (item != NULL)
    {
        findTreeAll(list, item->get_left(), s_count, s_tree, s_treeAll);
        findTree(item->get_ident(), s_count, s_tree);
        s_treeAll += s_tree;
        findTreeAll(list, item->get_right(), s_count, s_tree, s_treeAll);
    }*/
}

void MainWindow::findHash(QString str, int &s_count, int &s_hash)
{
    //алгоритм поиска номер 2 - рехэширование
    QStringList res = hTable.Find(str, s_count, s_hash);
    if(res[0] == "true")
        ui->label_14->setText(trUtf8("Идентификатор найден"));
    else ui->label_14->setText(trUtf8("Идентификатор не найден"));
}

void MainWindow::findHashAll(QStringList list, int &s_count, int &s_hash, int &s_hashAll)
{
    QStringList res = hTable.FindAll(list, s_count, s_hash, s_hashAll);
    if(res[0] == "true")
        ui->label_14->setText(trUtf8("Идентификатор найден"));
    else
        ui->label_14->setText(trUtf8("Идентификатор не найден"));
}

void MainWindow::ShowTree(Tree * item, int level)
{
    if(item)
    {
        ShowTree(item->get_left(), level+1);
        for (int i = 0; i < level; i++)
            ui->tree->setText(ui->tree->toPlainText() + "     ");
        ui->tree->setText(ui->tree->toPlainText() + item->get_ident() + "\n");
        ShowTree(item->get_right(), level+1);
    }
}

void MainWindow::DeleteTree(Tree * item)
{
    if(item != NULL)
    {
        DeleteTree(item->get_left());
        DeleteTree(item->get_right());
        delete item;
    }
}



void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->lineEdit_ident->setText(item->text());
}
