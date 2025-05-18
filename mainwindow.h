#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>

#include "AVL.cpp"
#include "Treap.cpp"
#include "RedBlack.cpp"
#include "SplayTree.cpp"
#include "BTree.cpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void AVLButtonClciked();
    void RedBlackButtonClicked();
    void BTreeButtonClicked();
    void SplayButtonClicked();
    void TreapButtonClicked();
    bool eventFilter(QObject *watched, QEvent *event);

    QGraphicsScene *scene;
    QGraphicsView *view;

    void Print();
    void PrintAVL(AVLNode<long long>* t,int x_prev,int y_prev);
    void PrintTreap(TreapNode<long long>* t,int x_prev,int y_prev);
    void PrintRedBlack(RedBlackNode<long long>* t,int x_prev,int y_prev);
    void PrintSplayTree(SplayNode<long long>* t,int x_prev,int y_prev);
    void PrintBTree(BNode<long long>* t,int x_prev,int y_prev);
private slots:
    void ZoomPlus();
    void ZoomMinus();

    //void UpdateAnimation();
};
#endif // MAINWINDOW_H
