#include "wizardscene.h"

WizardScene::WizardScene(QMenu* itemMenu_, QObject* parent)
    : QGraphicsScene(parent)
{
    itemMenu = itemMenu_;
    lineColor = Qt::black;
}

void WizardScene::setLineColor(const QColor &color)
{
    lineColor = color;
}

