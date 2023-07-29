#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct box {
    QRect rect;
    QColor color;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void new_line();
    QColor another_one(QColor cur);
    void remove_line(int collum);

private:
    int timerId, scale = 80, length = 10;
    box player;
    QList<QVector<box>> play_field;
    const QList<QColor> colors = {QColor("Lime"), QColor("Yellow"),
                              QColor("Blue"), QColor("Red"), QColor("Magenta")};
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
