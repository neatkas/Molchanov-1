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
    QFile file(pathToFile);
    bool opened = 1;
    if (!file.open(QFile::ReadOnly))
    {
        opened = 0;
        QMessageBox::warning(this, tr("Application"), tr("Cannot open file %1:\n%2.").arg(pathToFile));
        return;
    }

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
}

void MainWindow::on_pushButton_4_clicked()   //кнопка "Сброс"
{
    ui->lineEdit_ident->setText("");
    search_count = 0;
    ui->label_count->setText("");
    ui->label_14->setText("Идентификатор");
    ui->label_24->setText("Идентификатор");
}

void MainWindow::on_pushButton_3_clicked()   //кнопка "Поиск"
{
    if(ui->lineEdit_ident->text() != "")
    {
        findTree(ui->lineEdit_ident->text(), search_count);
        findHash(ui->lineEdit_ident->text(), search_count);
    }
    else
    {
        //вывести ошибку - Введите идентификатор!
    }
    ui->label_count->setText(QString::number(search_count));
}

void MainWindow::on_pushButton_5_clicked()   //кнопка "Найти все"
{
    findTreeAll(head, search_count);
    findHashAll(search_count);
    ui->label_count->setText(QString::number(search_count));
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


bool MainWindow::findTree(QString str, int &s_count)
{
    //алгоритм поиска номер 1 - бинарное дерево

    s_count++;

    int h = HashFun(str);

    Tree * temp = head;
    bool found = false;

    while(temp && !found)
    {
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

void MainWindow::findTreeAll(Tree * item, int &s_count)
{
    if (item != NULL)
    {
        findTreeAll(item->get_left(), s_count);
        findTree(item->get_ident(), s_count);
        findTreeAll(item->get_right(), s_count);
    }
}

void MainWindow::findHash(QString str, int &s_count)
{
    //алгоритм поиска номер 2 - рехэширование
    QStringList res = hTable.Find(str, s_count);
    if(res[0] == "true")
        ui->label_14->setText(trUtf8("Идентификатор найден"));
    else ui->label_14->setText(trUtf8("Идентификатор не найден"));
}

void MainWindow::findHashAll(int &s_count)
{
    QStringList res = hTable.FindAll(s_count);
    if(res[0] == "true")
        ui->label_14->setText(trUtf8("Идентификатор найден"));
    else
        ui->label_14->setText(trUtf8("Идентификатор не найден"));
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
