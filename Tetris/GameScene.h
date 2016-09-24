#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>

#include "Cell.h"
#include "Block.h"

class GameScene : public QGraphicsScene
{
//此类的对象当作游戏的窗口使用

    Q_OBJECT
public:
    explicit GameScene(QObject *parent = 0);

signals:
    void newScore(int scr); //告知其它对象新分数
    void endGame();       //告知其它对象游戏已结束
    void newBlock(Shape shp,QBrush color,BlockType type);
    //告知其它对象新俄罗斯方块的信息

public slots:
    void rotate();   //旋转当前方块
    void moveLeft(); //当前方块左移
    void moveRight(); //当前方块右移
    void moveDown();  //当前方块下移
    void startGame(); //开始新游戏
    void pauseGame(); //暂停游戏
    void resumeGame(); //继续游戏

private:
    bool collision(Shape shp,Position pos);      //检测是否接触边界以及底下的方块堆
    void printBlock(Shape shp,Position pos);      //显示俄罗斯方块
    void eraseBlock(Shape shp,Position pos);       //擦除俄罗斯方块
    void eraseFullLine();   //擦除满的一行
    void checkGameOver();   //检查游戏是否结束

    static const Position initPosList[7];

    Cell *grid[13][21];     //13*21个格子将构成游戏窗口的主体部分，用于显示方块
    Block currentBlock;      //正在下落的俄罗斯方块，也是我们唯一能控制的俄罗斯方块
    Block nextBlock;          //下一个方块
    Position currentBlockPos;   //正在下落的方块在窗口中的位置
    int score;          //得分，消掉一行得一分
    QTimer *timer;         //计时器，用于设置画面刷新速度
    QGraphicsTextItem *messageBoard;      //显示游戏结束时的信息
    bool start,pause;   //储存游戏是否开始以及是否暂停的信息
};

#endif // GAMESCENE_H
