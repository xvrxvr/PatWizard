#include "wizardscene.h"

WizardScene::WizardScene(QMenu* itemMenu, QObject* parent)
    : QGraphicsScene(parent)
{
    mItemMenu  = itemMenu;
    mLineColor = Qt::black;
}

void WizardScene::setLineColor(const QColor &color)
{
    mLineColor = color;
}

