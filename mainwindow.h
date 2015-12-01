#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WizardScene;

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openFile();
    void about();

private:
    //should be used in constructor for building menu entries callbacks.
    void createActions();
    void createMenus();
    void createToolBox();



    QMenu *fileMenu;
    QMenu *aboutMenu;

    QAction *openFileAction;
    QAction *aboutAction;
};

#endif // MAINWINDOW_H
