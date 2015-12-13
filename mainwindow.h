#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFutureWatcher>

//Forward decl.
class WizardScene;
class GrReaderFabric;
class GrReader;
class QToolButton;
class QButtonGroup;
class GemetrySolver;
class GrObject;

QT_BEGIN_NAMESPACE
class QAction;
class QGraphicsView;
class QComboBox;
class QToolBox;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    enum Mode { usual=0, addConstrain=1};

private slots:
    void openFile();
    void about();
    void sceneScaleChanged(const QString &scale);
    void addConstrModeApply(bool);
    void calculateConstrains();

private:
    //should be used in constructor for building menu entries callbacks.
    void createActions();
    void createMenus();
    void createToolBar();
    void createToolBox();
    void drawCircuit();

    WizardScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *aboutMenu;
    QStatusBar *status;
    QToolBar *pointerToolbar;
    QComboBox *sceneScaleCombo;
    QToolBox *toolBox;

    QAction *openFileAction;
    QAction *aboutAction;
    QAction *toolbarAddConstrAction;
    QAction *toolbarCalcConstrAction;

    QToolButton *addConstrButton;
    QToolButton *calcConstrainsButton;
    GemetrySolver* solver;
    QVector<GrObject*> objects;
    QFutureWatcher<bool> calculationWatcher;

/*
    QVector<GrObject*> objects;
    applyChanges(QVector<delta> v) {
        for i in v:
            toChange = objects.find(v);
            toChange
    }
*/

};

#endif // MAINWINDOW_H
