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
    explicit WizardScene(QMenu* itemMenu, QObject* parent=0);
    QColor lineColor() const { return mLineColor;}
    void setLineColor(const QColor& color);

private:
    QMenu* mItemMenu;
    QColor mLineColor;

};

#endif // WIZARDSCENE_H
