#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerId = startTimer(10);

    setMinimumSize(scale*5, scale*10);
    show();

    for (int i = 0; i < length; i++) new_line();
    player = {QRect(play_field[0][2].rect.x(), play_field[0][2].rect.y()-scale, scale, scale), another_one(play_field[0][2].color)};
    repaint();
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    if (player.rect.y() > 0) {
        for (int i = 0; i < play_field.size(); i++) {
            for (int j = 0; j < 5; j++) {
                play_field[i][j].rect.moveTop(play_field[i][j].rect.y() - 1);
            }
        }
        player.rect.moveTop(player.rect.y() - 1);
        repaint();
    } else {
        killTimer(timerId);
        QMessageBox msg;
        msg.setText("LOSER");
        msg.exec();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (int i = 0; i < play_field.size(); i++) {
        for (int j = 0; j < 5; j++) {
            painter.setBrush(QBrush(play_field[i][j].color));
            painter.drawRect(play_field[i][j].rect);
        }
    }
    painter.setBrush(QBrush(player.color));
    painter.drawRect(player.rect);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->x() >= 0 && event->x() <= 5*scale) {
        player.rect.moveLeft(event->x()/scale*scale);
        remove_line(event->x()/scale);
    }
}

void MainWindow::new_line()
{
    QList<QColor> temp(colors);
    QVector<box> line;
    for (int i = 0;  i< 5; i++) {
        int r = rand() % (5-i);
        if (play_field.size() == 0) line.push_back({QRect(i*scale, scale*length, scale, scale), temp[r]});
        else line.push_back({QRect(play_field.last()[i].rect.x(), play_field.last()[i].rect.y() + scale, scale, scale), temp[r]});
        temp.removeAt(r);
    }
    play_field.push_back(line);
}

QColor MainWindow::another_one(QColor cur)
{
    QColor result;
    do {
        result = colors[rand()%5];
    } while (cur == result);
    return result;
}

void MainWindow::remove_line(int collum)
{
    if (player.color == play_field[0][collum].color) {
        play_field.pop_front();
        player.rect.moveTop(player.rect.top() + scale);
        new_line();
        remove_line(collum);
        if (player.color != play_field[0][collum].color) player.color = another_one(play_field[0][collum].color);
    }
}
