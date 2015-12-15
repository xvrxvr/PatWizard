#ifndef WIZARDSCENE_H
#define WIZARDSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPainter>

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


class WizardLineItem: public QGraphicsLineItem {
public:
    WizardLineItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0) :
        QGraphicsLineItem(x1, y1, x2, y2, parent), p1(x1, y1), p2(x2, y2) {}

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

private:
    QPointF p1, p2;
};


class WizardArcItem : public QGraphicsEllipseItem {
public:
    WizardArcItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0 ) :
        QGraphicsEllipseItem(x, y, width, height, parent) {}

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};


class WizardPointItem : public QGraphicsEllipseItem {
public:
    WizardPointItem(qreal x, qreal y, QGraphicsItem * parent = 0) :
        QGraphicsEllipseItem(x - RADIUS, y - RADIUS, RADIUS, RADIUS, parent) {}

private:
    const qreal RADIUS;
};

#endif // WIZARDSCENE_H
