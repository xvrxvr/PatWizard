#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "wizardscene.h"

WizardScene::WizardScene(QMenu* itemMenu_, QObject* parent)
    : QGraphicsScene(parent)
{
    itemMenu = itemMenu_;
    lineColor = Qt::black;
    addRect(300, 200, 100, 200);
}

void WizardScene::setLineColor(const QColor &color)
{
    lineColor = color;
}


void WizardLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen());
    painter->drawLine(p1, p2);
}

void WizardLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }
    qDebug() << "selected whole item!";
    this->setSelected(true);
    this->setPen(QPen(Qt::blue));
    qDebug() << this->isSelected();
}


void WizardArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawArc(rect(), startAngle(), spanAngle());

    //if (option->state & QStyle::State_Selected)
    //  qt_graphicsItem_highlightSelected(this, painter, option);
}


const qreal WizardPointItem::RADIUS = 2.0;
