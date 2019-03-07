#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "tree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void CreateTree();
    void CreateHash();

    bool findTree(QString str, int &s_count, int &s_tree);
    void findTreeAll(QStringList list, Tree * item, int &s_count, int &s_tree, int &s_treeAll);
    void findHash(QString str, int &s_count, int &s_hash);
    void findHashAll(QStringList list, int &s_count, int &s_hash, int &s_hashAll);

    void ShowTree(Tree * item, int level);

    void DeleteTree(Tree * item);



    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
