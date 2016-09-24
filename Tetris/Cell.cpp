
#include "Cell.h"

Cell::Cell(QGraphicsItem *parents) : QGraphicsRectItem(parents)
{
    //构建一个原点在（0,0）（原点在左上角），长和宽均为30像素的方形
    setRect(0,0,30,30);
}
