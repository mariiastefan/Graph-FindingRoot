#include "QMainWindow.h"
#include "node.h"
#include "graf.h"
#include "arc.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QWidget>
#include <QRadioButton>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QtMath>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
   /* drawNode = false;
    drawArc = false;
    isOriented = false;*/
    ui->setupUi(this);
    
}

void MainWindow::mouseReleaseEvent(QMouseEvent* e)
{
    drawNode = false;
    drawArc = false;
    if (e->button() == Qt::RightButton)
    {
        Node n(e->pos());
        std::vector<Node> noduri;
        noduri = g.GetNoduri();
        for (auto index : noduri)
        {
            if (fabs(index.getPoint().rx() - e->pos().rx()) < 20 && fabs(index.getPoint().ry() - e->pos().ry()) < 20)
            {
                return;
            }
        }
        {
            g.AddNod(n);
            drawNode = true;
            update();
            firstNode = Node();
        }
    }
    else
    {
        QPointF p = e->localPos();
        std::vector<Node> noduri = g.GetNoduri();
        Node foundNode;
        for (auto& n : noduri)
        {
            if (fabs(n.getPoint().x() - p.x()) < 20 && fabs(n.getPoint().y() - p.y()) < 20)
            {
                foundNode = n;
                break;
            }
        }
        if (foundNode.getNumber() == -1)
            return;
        if (firstNode.getNumber() == -1)
        {
            firstNode = foundNode;
        }
        else
        {

            secondNode = foundNode;
            g.AddArc(Arc(firstNode, secondNode));
            firstNode = Node();
            secondNode = Node();
            drawArc = true;
            update();
        }
    }

}
void Sageata(QPainter& painter, QPoint start, QPoint end) {

    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal arrowSize = 20;
    painter.setPen(Qt::darkCyan);
    painter.setBrush(Qt::darkCyan);

    QLineF line(end, start);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
        cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
        cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);

}
void MainWindow::paintEvent(QPaintEvent* event)
{

    if (g.getNumberofNodes())
    {
        QPainter p(this);
        std::vector<Node> noduri = g.GetNoduri();
        for (auto& nod : noduri)
        {
            QRect r(nod.getPoint().x() - 10, nod.getPoint().y() - 10, 20, 20);
            p.setPen(QPen(Qt::white));
            p.setBrush(QBrush(Qt::magenta));
            p.drawEllipse(r);
            p.drawText(r,Qt::AlignCenter, QString::number(nod.getNumber()));
        }
        std::vector<Arc> arce1 = g.GetArce();
        for (auto& ind : arce1)
        {
                Sageata(p, ind.getFirstPoint().getPoint(), ind.getSecondPoint().getPoint());
        }
       
    }
}

MainWindow::~MainWindow()
{
    g.gasireaRadacinii();
    delete ui;
}




