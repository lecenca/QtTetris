#include <QBrush>

#include "BlockScene.h"
#include "Cell.h"

//各俄罗斯方块原点块的位置（以像素为单位）
const Position BlockScene::posList[7] = {
    {60,45},{60,45},{30,45},{30,60},{45,30},{45,30},{45,30}};

BlockScene::BlockScene(QObject *parent) : QGraphicsScene(parent)
{
    for(int i = 0;i<4;++i){
        cell[i] = new Cell();
        cell[i]->setVisible(false);
        addItem(cell[i]);
        //初始化，BlockScene窗口大小设置为120*120像素
        setSceneRect(0,0,120,120);
    }
}

void BlockScene::printBlock(Shape shp,QBrush color,BlockType type)
//函数接收表示形状，颜色，类型的参数
{
    //通过类型参数获取原点块的在BlockScene窗口的位置
    Position pos = posList[type];
    int x,y;
    //通过shp和原点块位置pos算出每一个块的位置
    for(int i = 0;i<4;++i){
        x = shp[i].x*30 + pos.x;
        y = shp[i].y*30 + pos.y;
        cell[i]->setPos(x,y);
        cell[i]->setBrush(color); //给描绘出来的俄罗斯方块上色
        cell[i]->setVisible(true);
    }
}
