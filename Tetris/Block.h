#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <QBrush>

struct Position
{
//此类的对象用于表示位置
    int x,y;

    Position operator+(Position other)
    //此函数使位置能像向量一样相加
    {
        Position t;
        t.x = x + other.x;
        t.y = y + other.y;
        return t;
    }
    bool operator==(Position other)
    //此函数用于比较两个Position对象是否相等
    {
        return x==other.x&&y==other.y;
    }
};


//Shape类用于定义俄罗斯方块的形状，具体思路如下
//
//所有俄罗斯方块均由方块组成，对任一俄罗斯方块，选定一个块作为原点，姑且称作原点块，则其它块
//与原点块的相对位置可通过坐标来表示，即Position对象，把一个俄罗斯方块的所有方块的坐标打包在
//一起作为一个对象，就成为了可以表示俄罗斯方块形状的对象，由于所有俄罗斯方块均只有4个方块，因
//而以std::array<Position,4>作为俄罗斯方块的形状类。
using Shape = std::array<Position,4>;


//BlockType类对象用于表示俄罗斯方块的类型。
enum BlockType
{
    IBLOCK = 0,
    JBLOCK = 1,
    LBLOCK = 2,
    OBLOCK = 3,
    ZBLOCK = 4,
    TBLOCK = 5,
    SBLOCK = 6
};

//Block类对象用于表示俄罗斯方块
class Block
{
public:
    Block();
    void rotate();    //旋转
    Shape tryRotate(); //把旋转后的结果以形状对象返回，但俄罗斯方块本身不旋转，用于检测碰撞
    Shape getShape();  //返回形状
    BlockType getType(); //返回俄罗斯方块的类型
    QBrush getColor(); //返回颜色

private:
    static const Shape shapeList[7];    //储存了所有俄罗斯方块的形状
    static const QBrush colorList[7];    //储存了俄罗斯方块可选的颜色
    static const BlockType blockTypeList[7];  //储存了所有俄罗斯方块的类型

    Shape shape;
    BlockType type;
    QBrush color;
};

#endif // BLOCK_H
