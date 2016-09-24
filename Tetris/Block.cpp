#include <QtGlobal>
#include <QBrush>

#include "Block.h"

//形状
const Shape Block::shapeList[7] = {
        {{ {0,0},{1,0},{-1,0},{-2,0} }},
        {{ {0,0},{0,1},{0,-1},{-1,-1} }},
        {{ {0,0},{0,1},{0,-1},{1,-1} }},
        {{ {0,0},{1,0},{1,-1},{0,-1} }},
        {{ {0,0},{0,1},{1,1},{-1,0} }},
        {{ {0,0},{0,1},{1,0},{-1,0} }},
        {{ {0,0},{0,1},{-1,1},{1,0} }}
        };

//颜色
const QBrush Block::colorList[7] = {
    QBrush(Qt::green),QBrush(Qt::cyan),QBrush(Qt::magenta),QBrush(Qt::yellow),
    QBrush(QColor(109,158,235)),QBrush(QColor(158,63,180)),QBrush(QColor(10,174,44))};

//类型
const BlockType Block::blockTypeList[7] = {
    IBLOCK,JBLOCK,LBLOCK,OBLOCK,ZBLOCK,TBLOCK,SBLOCK};

Block::Block()
{
    int i = qrand()%7;
    shape = shapeList[i]; //随机选择形状
    type = blockTypeList[i]; //选择形状对应的类型
    i = qrand()%7;
    color = colorList[i]; //随机选择颜色
}

void Block::rotate()
{
    if(type==OBLOCK)
        return;
    int t;
    //此处是一个旋转函数，(x,y)->(y,-x)
    for(unsigned i = 0;i<4;++i)
    {
        t = shape[i].x;
        shape[i].x = shape[i].y;
        shape[i].y = -t;
    }
}

Shape Block::tryRotate()
{
    //此函数与void rotate()类似，但不旋转俄罗斯方块本身，而是返回假设旋转后的结果
    if(type==OBLOCK)
        return shape;
    Shape shp = shape;
    int t;
    for(unsigned i = 0;i<4;++i)
    {
        t = shp[i].x;
        shp[i].x = shp[i].y;
        shp[i].y = -t;
    }
    return shp;
}

Shape Block::getShape()
{return shape;}

BlockType Block::getType()
{return type;}

QBrush Block::getColor()
{return color;}



