
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QPushButton>
#include<QTimer>
#include<QPainter>
#include<QLineEdit>
#include<QValidator>
#include <QWidget>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsRectItem>
#include<QGraphicsEllipseItem>
#include<QMouseEvent>
#include<QShortcut>
#include<string>
#include<QString>
#include<iostream>

int last = 0;
const int Update = 30;
int block_size_x = 30;
std::vector<int> blocks_size;
int max_log = 0;
int block_size_y = 20;
const int start_x = 0;
const int start_y = 0;
const double scale_factor = 1.1;
AVL avl;
Treap<int> treap;
RedBlack<int> red_black;
SplayTree<int> splay;
BTree<int> btree;


std::mt19937_64 rng(69);

void EraseFromTree(int x){
    avl.Erase(x);
    treap.Erase(x);
    red_black.Erase(x);
    splay.Erase(x);
    btree.EraseFirstStep(x);
    if(avl.root == nullptr){
        max_log = 0;
    }else{
        std::string help = std::to_string(FindMaxValue(avl.root)->num);
        max_log = help.size();
    }
}

void InsertToTree(int x){
    avl.Insert(x);
    treap.Insert(x);
    red_black.Insert(x);
    splay.Insert(x);
    btree.Insert(x);

    std::string help = std::to_string(FindMaxValue(avl.root)->num);
    max_log = help.size();
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),scene(new QGraphicsScene(this)),view(new QGraphicsView(this))
{
    ui->setupUi(this);

    for(int i = 0;i <= 18;i++){
        blocks_size.push_back(7 * (i + 2));
    }


    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::Print);
    timer->start(Update);

    view->setScene(scene);
    view->setInteractive(true);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    setCentralWidget(view);

     view->viewport()->installEventFilter(this);


     QPalette palette = view->palette();
     palette.setColor(QPalette::Base, QColor(20, 20, 50)); // Темно-серый фон
     view->setPalette(palette);
     view->setAutoFillBackground(true);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_K), this, SLOT(ZoomPlus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this, SLOT(ZoomMinus()));

    QPushButton* AVLbutton = new QPushButton("AVL",this);
    AVLbutton->setGeometry(0,0,80,50);
    connect(AVLbutton,&QPushButton::clicked,this,&MainWindow::AVLButtonClciked);

    QPushButton* RedBlackbutton = new QPushButton("RedBlack",this);
    RedBlackbutton->setGeometry(80,0,80,50);
    connect(RedBlackbutton,&QPushButton::clicked,this,&MainWindow::RedBlackButtonClicked);

    QPushButton* BTreebutton = new QPushButton("BTree",this);
    BTreebutton->setGeometry(160,0,80,50);
    connect(BTreebutton,&QPushButton::clicked,this,&MainWindow::BTreeButtonClicked);

    QPushButton* SplayButton = new QPushButton("Splay",this);
    SplayButton->setGeometry(240,0,80,50);
    connect(SplayButton,&QPushButton::clicked,this,&MainWindow::SplayButtonClicked);

    QPushButton* TreapButton = new QPushButton("Treap",this);
    TreapButton->setGeometry(320,0,80,50);
    connect(TreapButton,&QPushButton::clicked,this,&MainWindow::TreapButtonClicked);

    QLineEdit *Insert = new QLineEdit(this);
    Insert->setValidator(new QIntValidator(0, 1e9, this));
    Insert->setGeometry(480,0,80,50);

    QPushButton* InsertOne = new QPushButton("Add",this);
    InsertOne->setGeometry(400,0,80,50);
    connect(InsertOne,&QPushButton::clicked,this,[Insert](){
        bool ok;
        int intValue = Insert->text().toInt(&ok);
        InsertToTree(intValue);
    });

    QLineEdit *InsertMany = new QLineEdit(this);
    InsertMany->setValidator(new QIntValidator(0, 1e4, this));
    InsertMany->setGeometry(640,0,80,50);

    QPushButton* InsertManyB = new QPushButton("Add Many",this);
    InsertManyB->setGeometry(560,0,80,50);
    connect(InsertManyB,&QPushButton::clicked,this,[InsertMany](){
        bool ok;
        int intValue = InsertMany->text().toInt(&ok);
        while(intValue > 0){
            int tmp = rng() % 100000;
            InsertToTree(tmp);
            intValue--;
        }
    });
}



bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && QApplication::mouseButtons() == Qt::LeftButton){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos = view->mapToScene(mouseEvent->pos());
        QGraphicsItem *item = scene->itemAt(scenePos, QTransform());
        if (item && item->type() == QGraphicsTextItem::Type) {
            QGraphicsTextItem* textItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);

            EraseFromTree(std::stoi((textItem->toPlainText()).toStdString()));
        }else if(item && item->type() == QGraphicsRectItem::Type){
            QGraphicsRectItem* RectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
            QPointF help_pos = QPointF(RectItem->rect().x(),RectItem->rect().y());
            QGraphicsItem *item1 = scene->itemAt(help_pos, QTransform());
            if(item1 && item1->type() == QGraphicsTextItem::Type){
                QGraphicsTextItem* textItem = qgraphicsitem_cast<QGraphicsTextItem*>(item1);
                EraseFromTree(std::stoi((textItem->toPlainText()).toStdString()));
            }
        }
        return true;
    }
    return QMainWindow::eventFilter(watched, event);;
}



void MainWindow::ZoomPlus(){
    view->scale(scale_factor,scale_factor);
}

void MainWindow::ZoomMinus(){
     view->scale(1.0 / scale_factor,1.0 / scale_factor);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::AVLButtonClciked(){
    last = 0;
}

void MainWindow::RedBlackButtonClicked(){
    last = 1;
}

void MainWindow::BTreeButtonClicked(){
    last = 2;
}
void MainWindow::SplayButtonClicked(){
    last = 3;
}

void MainWindow::TreapButtonClicked(){
    last = 4;
}

void MainWindow::PrintAVL(AVLNode* t,int x_prev,int y_prev){
    if(t == nullptr)return;
    QGraphicsRectItem *rect = scene->addRect(x_prev + t->x,y_prev + t->y, block_size_x, block_size_y);
    rect->setBrush(Qt::white);
    std::string ty = std::to_string(t->num);
    QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(t->num)));
    QRectF textRect = text->boundingRect();
    text->setPos(
        rect->rect().center().x() - textRect.width() / 2,
        rect->rect().center().y() - textRect.height() / 2
        );
    text->setDefaultTextColor(Qt::red);
    QGraphicsLineItem* line = scene->addLine(block_size_x / 2 + x_prev,y_prev + block_size_y,
                                             (x_prev + t->x) + block_size_x /2, y_prev + t->y);
    line->setPen(QPen(Qt::red, 2));
    PrintAVL(t->left,x_prev + t->x,y_prev + t->y);
    PrintAVL(t->right,x_prev + t->x,y_prev + t->y);
}

void MainWindow::PrintTreap(TreapNode<int>* t,int x_prev,int y_prev){
    if(t == nullptr)return;
    QGraphicsRectItem *rect = scene->addRect(x_prev + t->x,y_prev + t->y, block_size_x, block_size_y);
    rect->setBrush(Qt::white);
    std::string ty = std::to_string(t->num);
    QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(t->num)));
    QRectF textRect = text->boundingRect();
    text->setPos(
        rect->rect().center().x() - textRect.width() / 2,
        rect->rect().center().y() - textRect.height() / 2
        );
    text->setDefaultTextColor(Qt::red);
    QGraphicsLineItem* line = scene->addLine(block_size_x / 2 + x_prev,y_prev + block_size_y,
                                             (x_prev + t->x) + block_size_x /2, y_prev + t->y);
    line->setPen(QPen(Qt::red, 2));
    PrintTreap(t->left,x_prev + t->x,y_prev + t->y);
    PrintTreap(t->right,x_prev + t->x,y_prev + t->y);
}

void MainWindow::PrintRedBlack(RedBlackNode<int>* t,int x_prev,int y_prev){
    if(t == nullptr)return;
    QGraphicsRectItem *rect = scene->addRect(x_prev + t->x,y_prev + t->y, block_size_x, block_size_y);
    if(t->is_red){
        rect->setBrush(Qt::red);
    }else{
        rect->setBrush(Qt::black);
    }
    std::string ty = std::to_string(t->num);
    QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(t->num)));
    QRectF textRect = text->boundingRect();
    text->setPos(
        rect->rect().center().x() - textRect.width() / 2,
        rect->rect().center().y() - textRect.height() / 2
        );
    text->setDefaultTextColor(Qt::white);
    QGraphicsLineItem* line = scene->addLine(block_size_x / 2 + x_prev,y_prev + block_size_y,
                                             (x_prev + t->x) + block_size_x /2, y_prev + t->y);
    line->setPen(QPen(Qt::yellow, 2));
    PrintRedBlack(t->left,x_prev + t->x,y_prev + t->y);
    PrintRedBlack(t->right,x_prev + t->x,y_prev + t->y);
}

void MainWindow::PrintSplayTree(SplayNode<int>* t,int x_prev,int y_prev){
    if(t == nullptr)return;
    QGraphicsRectItem *rect = scene->addRect(x_prev + t->x,y_prev + t->y, block_size_x, block_size_y);
    rect->setBrush(Qt::white);
    std::string ty = std::to_string(t->num);
    QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(t->num)));
    QRectF textRect = text->boundingRect();
    text->setPos(
        rect->rect().center().x() - textRect.width() / 2,
        rect->rect().center().y() - textRect.height() / 2
        );
    text->setDefaultTextColor(Qt::red);
    QGraphicsLineItem* line = scene->addLine(block_size_x / 2 + x_prev,y_prev + block_size_y,
                                             (x_prev + t->x) + block_size_x /2, y_prev + t->y);
    line->setPen(QPen(Qt::red, 2));
    PrintSplayTree(t->left,x_prev + t->x,y_prev + t->y);
    PrintSplayTree(t->right,x_prev + t->x,y_prev + t->y);
}

void MainWindow::PrintBTree(BNode<int>* t,int x_prev,int y_prev){
    if(t == nullptr){
        return;
    }
    int start_x = t->coor_x[0] + x_prev;
    int stop_x = t->coor_x.back() + x_prev + block_size_x;
    int help_x = 0;
    int help_y = 0;
    for(int i = 0;i < t->parent->childs.size();i++){
        if(t->parent->childs[i] == t){
            help_x = x_prev + i * block_size_x;
            help_y = y_prev + block_size_y;
        }
    }
    QGraphicsLineItem* line = scene->addLine((start_x + stop_x) / 2,t->coor_y[0] + y_prev,help_x,help_y);
    line->setPen(QPen(Qt::red, 2));

    for(int i = 0;i < t->num.size();i++){
        QGraphicsRectItem *rect = scene->addRect(start_x + i * block_size_x,t->coor_y[i] + y_prev, block_size_x, block_size_y);
        rect->setBrush(Qt::white);
        QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(t->num[i])));
        QRectF textRect = text->boundingRect();
        text->setPos(
            rect->rect().center().x() - textRect.width() / 2,
            rect->rect().center().y() - textRect.height() / 2
            );
        text->setDefaultTextColor(Qt::red);
    }
    for(int i = 0;i < t->childs.size();i++){
        PrintBTree(t->childs[i],t->coor_x[0] + x_prev,t->coor_y[0] + y_prev);
    }
}

void MainWindow::Print(){
    scene->clear();
    block_size_x = blocks_size[max_log];
    if(last == 0){
        avl.Print(avl.root,block_size_x);
        if(avl.root != nullptr){
            QGraphicsRectItem *rect = scene->addRect(start_x,start_y, block_size_x, block_size_y);
            rect->setBrush(Qt::white);
            QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(avl.root->num)));
            QRectF textRect = text->boundingRect();
            text->setPos(
                rect->rect().center().x() - textRect.width() / 2,
                rect->rect().center().y() - textRect.height() / 2
                );
            text->setDefaultTextColor(Qt::red);
            PrintAVL(avl.root->left,start_x,start_y);
            PrintAVL(avl.root->right,start_x,start_y);
        }
    }else if(last == 4){
        treap.Print(treap.root,block_size_x);
        if(treap.root != nullptr){
            QGraphicsRectItem *rect = scene->addRect(start_x,start_y, block_size_x, block_size_y);
            rect->setBrush(Qt::white);
            QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(treap.root->num)));
            QRectF textRect = text->boundingRect();
            text->setPos(
                rect->rect().center().x() - textRect.width() / 2,
                rect->rect().center().y() - textRect.height() / 2
                );
            text->setDefaultTextColor(Qt::red);
            PrintTreap(treap.root->left,start_x,start_y);
            PrintTreap(treap.root->right,start_x,start_y);
        }
    }else if(last == 1){
        red_black.Print(red_black.root,block_size_x);
        if(red_black.root != nullptr){
            QGraphicsRectItem *rect = scene->addRect(start_x,start_y, block_size_x, block_size_y);
            if(red_black.root->is_red){
                rect->setBrush(Qt::red);
            }else{
                rect->setBrush(Qt::black);
            }

            QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(red_black.root->num)));
            QRectF textRect = text->boundingRect();
            text->setPos(
                rect->rect().center().x() - textRect.width() / 2,
                rect->rect().center().y() - textRect.height() / 2
                );
            text->setDefaultTextColor(Qt::white);
            PrintRedBlack(red_black.root->left,start_x,start_y);
            PrintRedBlack(red_black.root->right,start_x,start_y);
        }
    }else if(last == 3){
        splay.Print(splay.root,block_size_x);
        if(splay.root != nullptr){
            QGraphicsRectItem *rect = scene->addRect(start_x,start_y, block_size_x, block_size_y);
            rect->setBrush(Qt::white);
            QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(splay.root->num)));
            QRectF textRect = text->boundingRect();
            text->setPos(
                rect->rect().center().x() - textRect.width() / 2,
                rect->rect().center().y() - textRect.height() / 2
                );
            text->setDefaultTextColor(Qt::red);
            PrintSplayTree(splay.root->left,start_x,start_y);
            PrintSplayTree(splay.root->right,start_x,start_y);
        }
    }else if(last == 2){
        btree.Print(btree.root,block_size_x);
        if(btree.root != nullptr){
            for(int i = 0;i < btree.root->num.size();i++){
                QGraphicsRectItem *rect = scene->addRect(start_x + i * block_size_x,start_y, block_size_x, block_size_y);
                rect->setBrush(Qt::white);
                QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(btree.root->num[i])));
                QRectF textRect = text->boundingRect();
                text->setPos(
                    rect->rect().center().x() - textRect.width() / 2,
                    rect->rect().center().y() - textRect.height() / 2
                    );
                text->setDefaultTextColor(Qt::red);
            }
            for(int i  = 0;i < btree.root->childs.size();i++){
                PrintBTree(btree.root->childs[i],start_x,start_y);
            }
        }
    }
}









