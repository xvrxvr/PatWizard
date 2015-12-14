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


void WizardArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawArc(rect(), startAngle(), spanAngle());

    //if (option->state & QStyle::State_Selected)
    //  qt_graphicsItem_highlightSelected(this, painter, option);
}
