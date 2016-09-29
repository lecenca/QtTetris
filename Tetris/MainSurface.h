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

private slots:
    void on_startRestartButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::Widget *ui;
    GameScene *playGround;
    BlockScene *nextBlockWindow;
    int score;

    void refreshScore(int sco);
    void gameOver();
};

#endif // WIDGET_H
