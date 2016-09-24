#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>

//此类用于表示最基本的方块，就是一个方形，是构建游戏场景与俄罗斯方块的基本单元

class Cell : public QGraphicsRectItem
{

public:
    Cell(QGraphicsItem *parents = Q_NULLPTR);

};

#endif // CELL_H
