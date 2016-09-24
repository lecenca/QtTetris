#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "GameScene.h"
#include "BlockScene.h"

namespace Ui {
class Widget;
}

class MainSurface : public QWidget
{
    Q_OBJECT

public:
    explicit MainSurface(QWidget *parent = 0);
    ~MainSurface();

protected:
    void keyPressEvent(QKeyEvent *event);
    //执行按键按下时对应的行为

private slots:
    void on_startRestartButton_clicked();
    //按下开始键的行为
    void on_quitButton_clicked();
    //按下退出键的行为

private:
    Ui::Widget *ui;  //界面对象
    GameScene *playGround; //游戏窗口对象
    BlockScene *nextBlockWindow; //显示下一个俄罗斯方块的对象
    int score; //分数

    void refreshScore(int sco); //更新分数
    void gameOver(); //结束游戏
};

#endif // WIDGET_H
