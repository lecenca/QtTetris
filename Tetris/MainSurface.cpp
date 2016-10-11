#include <QKeyEvent>
#include <QPalette>

#include "MainSurface.h"
#include "ui_widget.h"
#include "GameScene.h"
#include "BlockScene.h"

MainSurface::MainSurface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    playGround = new GameScene();
    ui->gameWindow->setScene(playGround);
    ui->gameWindow->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    nextBlockWindow = new BlockScene();
    ui->blockWindow->setScene(nextBlockWindow);
    ui->blockWindow->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    score = 0;
    ui->scoreLabel->setText("<h3>Score: 0</h3>");
    ui->startRestartButton->setText("Start");
    ui->quitButton->setText("Quit");

    //设置背景
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":res/background.png")));
    setPalette(palette);

    QObject::connect(playGround,GameScene::newScore,
                     this,MainSurface::refreshScore);
    QObject::connect(playGround,GameScene::endGame,
                     this,MainSurface::gameOver);
    QObject::connect(playGround,GameScene::newBlock,
                     nextBlockWindow,BlockScene::printBlock);
}

MainSurface::~MainSurface()
{
    delete ui;
}

void MainSurface::keyPressEvent(QKeyEvent *event)
{
    //设置按键，上、下、左、右分别对应旋转、下移、左移、右移
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
    //设置开始键，当键显示“开始”时，按下将会开始游戏，并且键变为“暂停”，
    //当键为“暂停”时，按下将暂停游戏，并且键变为“重启”
    //按下“重启”时，游戏将继续，键重新变为“暂停”
    //只有游戏结束时，键才会重新变为“开始”
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
    //响应GameScene的newScore信号，更新分数显示
    score = scr;
    ui->scoreLabel->setText(QString("<h3>Score: %1</h3>").arg(QString::number(score)));
}

void MainSurface::gameOver()
{
    //响应GameScene的endGame信号，把“暂停”键变为“开始”键
    ui->startRestartButton->setText("Start");
}

void MainSurface::on_quitButton_clicked()
{
    //按下“退出”键时，退出游戏
    close();
}
