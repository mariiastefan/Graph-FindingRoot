
#include "graf.h"
#include "ui_QMainWindow.h"
#include <QtWidgets/QMainWindow>
#include<QPushButton>
#include <QRadioButton>

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void paintEvent(QPaintEvent* event);
    ~MainWindow();
private:
    Ui::MainWindow* ui;
    Graf g;
    Node firstNode, secondNode;
    bool drawNode, drawArc, isOriented;


};

