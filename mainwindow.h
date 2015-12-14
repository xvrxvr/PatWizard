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
class QLineEdit;
class QDoubleSpinBox;
class QGroupBox;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    enum Mode { usualMode=0, addConstrainMode=1};

private slots:
    void openFile();
    void about();
    void sceneScaleChanged(const QString &scale);
    void applyAddConstrMode(bool);
    void calculateConstrains();
    void calcFinished();
    void addConstrain();

private:
    //should be used in constructor for building menu entries callbacks.
    void createActions();
    void createMenus();
    void createToolBar();
    void createToolBox();
    void drawCircuit();
    QGroupBox* makeConstrainGroupBox();

    Mode userMode;

    WizardScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *aboutMenu;
    QStatusBar *status;
    QToolBar *pointerToolbar;
    QComboBox *sceneScaleCombo;

    QToolBox *toolBox;
    QComboBox *constrainTypeCombo;
    QDoubleSpinBox *constrParam1SBox;
    QDoubleSpinBox *constrParam2SBox;

    QAction *openFileAction;
    QAction *aboutAction;
    QAction *toolbarAddConstrAction;
    QAction *toolbarCalcConstrAction;
    QAction *tboxAddConstrainAction;

    QToolButton *addConstrButton;
    QToolButton *calcConstrainsButton;
    bool calcPending;
    //GemetrySolver* solver;
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

// added for emulating async function call.
bool sleepy();

#endif // MAINWINDOW_H
