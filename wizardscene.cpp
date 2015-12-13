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

