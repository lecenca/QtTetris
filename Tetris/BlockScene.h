#ifndef BLOCKSCENE_H
#define BLOCKSCENE_H

#include <QGraphicsScene>
#include <QBrush>

#include "Cell.h"
#include "Block.h"

class BlockScene : public QGraphicsScene
{
//此类用于显示下一个出现的俄罗斯方块
    Q_OBJECT

public:
    BlockScene(QObject *parent = 0);
    //在窗口显示方块
    void printBlock(Shape shp,QBrush color,BlockType type);

private:
    //此数组用于储存每个俄罗斯方块原点块在BlockScene的位置
    static const Position posList[7];

    //因为只显示一个俄罗斯方块，所以有四个Cell对象就够了
    Cell *cell[4];
};

#endif // BLOCKSCENE_H
