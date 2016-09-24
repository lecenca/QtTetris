#include <QKeyEvent>

#include "MainSurface.h"
#include "ui_widget.h"
#include "GameScene.h"
#include "BlockScene.h"

MainSurface::MainSurface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //初始化各个对象
    ui->setupUi(this);
    playGround = new GameScene();
    ui->gameWindow->setScene(playGround);
    ui->gameWindow->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    nextBlockWindow = new BlockScene();
    ui->blockWindow->setScene(nextBlockWindow);
    ui->blockWindow->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    score = 0;
    ui->scoreLabel->setText("Score: 0");
    ui->startRestartButton->setText("Start");
    ui->quitButton->setText("Quit");


    //游戏窗口告知新分数时更新界面上的分数
    QObject::connect(playGround,GameScene::newScore,
                     this,MainSurface::refreshScore);
    //游戏结束时进行相关操作
    QObject::connect(playGround,GameScene::endGame,
                     this,MainSurface::gameOver);
    //游戏窗口告知新俄罗斯方块信息时将其画出来
    QObject::connect(playGround,GameScene::newBlock,
                     nextBlockWindow,BlockScene::printBlock);
}

MainSurface::~MainSurface()
{
    delete ui;
}

void MainSurface::keyPressEvent(QKeyEvent *event)
{
    //按下上，下，左，右时，分别进行旋转，下移，左移，右移操作，
    //对其它按键一律不处理
    switch (event->key()){
    case Qt::Key_Left:
        playGround->moveLeft();
        break;
    case Qt::Key_Right:
        playGround->moveRight();
        break;
    case Qt::Key_Up:
        playGround->rotate();
        break;
    case Qt::Key_Down:
        playGround->moveDown();
        break;
    default:
        break;
    }
}

void MainSurface::on_startRestartButton_clicked()
{
    //开始键按下后，功能变为暂停继续键，按键上的字也变为与功能相对应的单词，
    //本游戏不提供玩到一半重玩的功能，若想重玩，自行结束游戏
    QString text = ui->startRestartButton->text();
    if(text=="Start"){
        playGround->startGame();
        ui->startRestartButton->setText("Pause");
    }else if(text=="Pause"){
        playGround->pauseGame();
        ui->startRestartButton->setText("Resume");
    }else if(text=="Resume"){
        playGround->resumeGame();
        ui->startRestartButton->setText("Pause");
    }
}

void MainSurface::refreshScore(int scr)
{
    //更新分数
    score = scr;
    ui->scoreLabel->setText(QString("Score: %1").arg(QString::number(score)));
}

void MainSurface::gameOver()
{
    //将暂停继续键重置为开始键
    ui->startRestartButton->setText("Start");
}

void MainSurface::on_quitButton_clicked()
{
    //关闭整个程序
    close();
}
