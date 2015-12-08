#ifndef WIZARDSCENE_H
#define WIZARDSCENE_H

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QMenu;
class QColor;
class QFont;
class QPointF;
QT_END_NAMESPACE


class WizardScene : public QGraphicsScene
{
    Q_OBJECT

public:
    WizardScene(QMenu* itemMenu, QObject* parent=0);
    QColor getLineColor() const { return lineColor;}
    void setLineColor(const QColor& color);


private:
    QMenu* itemMenu;
    QColor lineColor;

};

#endif // WIZARDSCENE_H
