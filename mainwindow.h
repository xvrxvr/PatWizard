#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();

private:
    //should be used in constructor for building menu entries callbacks.
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QAction *openFileAction;
};

#endif // MAINWINDOW_H
