#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <QGraphicsTextItem>

#include "GameScene.h"
#include "Block.h"

//储存俄罗斯方块刚出现于游戏窗口时的位置
const Position GameScene::initPosList[7] = {
    {5,0},{6,1},{6,1},{5,1},{5,0},{6,0},{6,0}};

GameScene::GameScene(QObject *parent) : QGraphicsScene(parent)
{
    //初始化每个格子
    for(int i = 0;i<13;++i){
        for(int j = 0;j<=21;++j){
            grid[i][j] = new Cell();
            grid[i][j]->setPos(i*30,j*30);
            grid[i][j]->setVisible(false);
            addItem(grid[i][j]);
        }
    }
    setSceneRect(0,0,390,630); //将大小设置为390*630
    qsrand(QTime::currentTime().msec());  //给随机函数时间当种子，尽量让每次游戏不同
    start = pause = false;
    timer = new QTimer(this);
    timer->start(500);    //每500ms刷新一次界面
    messageBoard = new QGraphicsTextItem();
    addItem(messageBoard);
    messageBoard->setPos(90,270);   //设置结束信息的位置
    messageBoard->setVisible(false);
    //时间一到就用void moveDown()刷新界面
    QObject::connect(timer,&QTimer::timeout,
                     this,&GameScene::moveDown);
}

void GameScene::rotate()
{
    if(start==false||pause==true)
        return;   
    //当游戏开始并且不暂停时才能对俄罗斯方块进行操作，所有操作都将做此检查
    Shape shp = currentBlock.tryRotate();
    if(!collision(shp,currentBlockPos)){
        //检查无碰撞后才能进行操作，所有操作都要进行此检查
        eraseBlock(currentBlock.getShape(),currentBlockPos);  //擦除旧块
        currentBlock.rotate(); //旋转
        printBlock(shp,currentBlockPos); //描绘新块
    }
}

void GameScene::moveLeft()
{
    //与void GameScene::rotate()类似
    if(start==false||pause==true)
        return;
    Position p = currentBlockPos;
    Shape shp = currentBlock.getShape();
    --p.x;
    if(!collision(shp,p)){
        eraseBlock(shp,currentBlockPos);
        currentBlockPos = p;
        printBlock(shp,p);
    }
}

void GameScene::moveRight()
{
    //与void GameScene::rotate()类似
    if(start==false||pause==true)
        return;
    Position p = currentBlockPos;
    Shape shp = currentBlock.getShape();
    ++p.x;
    if(!collision(shp,p)){
        eraseBlock(shp,currentBlockPos);
        currentBlockPos = p;
        printBlock(shp,p);
    }
}

void GameScene::moveDown()
{
    if(start==false||pause==true)
        return;
    Shape shp = currentBlock.getShape();   
    Position p = currentBlockPos;
    ++p.y;
    if(collision(shp,p)){
        //若碰撞说明已到达块堆或已触及窗口顶部，因而要检查是否要结束游戏
        checkGameOver();
        //此处即使游戏结束任会继续进行，但只会多描绘一块俄罗斯方块，影响不大，故不处理
        currentBlock = nextBlock;
        nextBlock = Block();
        emit newBlock(nextBlock.getShape(),nextBlock.getColor(),nextBlock.getType());
        currentBlockPos = initPosList[currentBlock.getType()];
        eraseFullLine();
        printBlock(currentBlock.getShape(),currentBlockPos);
    }else{
        //此处与void GameScene::rotate()类似
        eraseBlock(shp,currentBlockPos);
        ++currentBlockPos.y;
        printBlock(shp,currentBlockPos);
    }
}

void GameScene::printBlock(Shape shp,Position pos)
{
    //由原点块位置pos以及形状shp计算出各块的位置并一一描绘
    for(int i = 0;i<4;++i){
        shp[i] = shp[i] + pos;
        grid[shp[i].x][shp[i].y]->setVisible(true);
        grid[shp[i].x][shp[i].y]->setBrush(currentBlock.getColor());
    }
}

void GameScene::eraseBlock(Shape shp,Position pos)
{
    //与void GameScene::printBlock(Shape shp,Position pos)类似，
    //不过将计算出的位置的方块擦除
    for(int i = 0;i<4;++i){
        shp[i] = shp[i] + pos;
        grid[shp[i].x][shp[i].y]->setVisible(false);
    }
}

bool GameScene::collision(Shape shp,Position pos)
{
    //检测碰撞
    bool flag = false;
    Shape curShp = currentBlock.getShape();
    for(int i = 0;i<4;++i){
        if(flag==true)
            break;
        shp[i] = shp[i] + pos;
        //检查是否碰到边界
        if(shp[i].x<0||
           shp[i].x>=13||
           shp[i].y<0||
           shp[i].y>=21){
            flag = true;
            break;
        }else if(grid[shp[i].x][shp[i].y]->isVisible()){
            //检查是否碰到块堆
            flag = true;
            for(int j = 0;j<4;++j){
                if(shp[i]==(curShp[j]+currentBlockPos)){
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}


void GameScene::startGame()
{
    //开始新游戏，清除上一次游戏的数据
    for(int x = 0;x<13;++x)
        for(int y = 0;y<21;++y)
            grid[x][y]->setVisible(false);
    //生成第一个俄罗斯方块和下一个俄罗斯方块
    currentBlock = Block();
    nextBlock = Block();
    //告诉其他对象下一个方块的信息
    emit newBlock(nextBlock.getShape(),nextBlock.getColor(),nextBlock.getType());
    currentBlockPos = initPosList[currentBlock.getType()];
    messageBoard->setVisible(false);
    //重置分数并告知其它对象新的分数
    score = 0;
    emit newScore(score);
    start = true;
}

void GameScene::pauseGame()
{pause = true;}

void GameScene::resumeGame()
{pause = false;}

void GameScene::eraseFullLine()
{
    bool full;
    int x,y;
    int scr = 0;
    //从上到下检查，但不检查最上面一行，若最上面一行有方块，则认定为游戏结束
    for(y = 20;y>0;--y){
        full = true;
        //检查第i行是否满
        for(x = 0;x<13;++x){
            if(!grid[x][y]->isVisible()){
                full = false;
                break;
            }
        }
        if(full){
            //满的话就消掉
            for(x = 0;x<13;++x){
                grid[x][y]->setVisible(false);
            }
            //消掉一行加一分
            ++scr;
        }else{
            //不满，则将这行往下移
            for(x = 0;x<13;++x){
                if(grid[x][y]->isVisible()){
                    grid[x][y]->setVisible(false);
                    //目前得到scr分，说明已经消了scr行，要往下移scr行
                    grid[x][y+scr]->setVisible(true);
                    grid[x][y+scr]->setBrush(grid[x][y]->brush());
                }
            }
        }
    }
    score += scr; //求出总分
    emit newScore(score); //告诉其他对象新的总分
}

void GameScene::checkGameOver()
{
    //检测最上面一行有没有方块，有就说明游戏结束
    for(int x = 0;x<13;++x){
        if(grid[x][0]->isVisible()){
            start = false;
            messageBoard->setHtml(QString("<h1>You total score is</h1></br>"
                                          "<h1>%1</h1>").arg(QString::number(score)));
            messageBoard->setVisible(true);
            emit endGame();   //告诉其他对象游戏已经结束
            break;
        }
    }
}




