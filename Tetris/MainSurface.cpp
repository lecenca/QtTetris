#include <QKeyEvent>

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
    ui->scoreLabel->setText("Score: 0");
    ui->startRestartButton->setText("Start");
    ui->quitButton->setText("Quit");


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
    score = scr;
    ui->scoreLabel->setText(QString("Score: %1").arg(QString::number(score)));
}

void MainSurface::gameOver()
{
    ui->startRestartButton->setText("Start");
}

void MainSurface::on_quitButton_clicked()
{
    close();
}
