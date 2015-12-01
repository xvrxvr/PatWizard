#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WizardScene;
class GrReaderFabric;
class GrReader;

QT_BEGIN_NAMESPACE
class QAction;
class QGraphicsView;
class QComboBox;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openFile();
    void about();
    void sceneScaleChanged(const QString &scale);

private:
    //should be used in constructor for building menu entries callbacks.
    void createActions();
    void createMenus();
    void createToolBox();

    WizardScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *aboutMenu;
    QStatusBar *status;
    QToolBar *pointerToolbar;
    QComboBox *sceneScaleCombo;

    QAction *openFileAction;
    QAction *aboutAction;

    GrReaderFabric* fabric;
    GrReader* reader;
};

#endif // MAINWINDOW_H
