#include "mainwindow.h"

//QT standard library
#include <QtWidgets>
#include <QToolButton>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>
#include <QThread>
#include <QGroupBox>
#include <QDoubleValidator>
#include <QDoubleSpinBox>
#include <QtCore/qmath.h>
// proj.specific headers
#include "wizardscene.h"
#include "gr_object.h"
//#include "GeometrySolver/gemetrysolver.h"

MainWindow::MainWindow() {
    createActions();
    createToolBar();
    createMenus();
    createToolBox();

    userMode = usualMode;

    scene = new WizardScene(fileMenu, this);
    scene->setSceneRect(QRectF(0, 0, 500, 500));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);

    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("PatWizard"));
    setUnifiedTitleAndToolBarOnMac(true);

    calcPending = false;
    status = statusBar();
    // Init gemetrySolver. Uncomment once it's implemented.
    //solver = new GemetrySolver();
    // TODO: add hardcode init of objects.
}


void MainWindow::createActions() {
    // action for opening file
    openFileAction = new QAction(tr("&File"), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open PCB file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // add action for addConstrain ToolButton.
    toolbarAddConstrAction = new QAction(this);
    toolbarAddConstrAction->setShortcut(tr("Ctrl+A"));
    toolbarAddConstrAction->setCheckable(true);
    toolbarAddConstrAction->setIconText(tr("AddConstrMode"));
    connect(toolbarAddConstrAction, SIGNAL(triggered(bool)), this, SLOT(applyAddConstrMode(bool)));

    // add action for calcConstrains ToolButton/
    toolbarCalcConstrAction = new QAction(this);
    toolbarCalcConstrAction->setShortcut(tr("Ctrl+C"));
    toolbarCalcConstrAction->setIconText(tr("Calc"));
    connect(toolbarCalcConstrAction, SIGNAL(triggered()), this, SLOT(calculateConstrains()));

    // add action for toolbox button "Add Constrain"
    tboxAddConstrainAction = new QAction(this);
    tboxAddConstrainAction->setIconText(tr("Add Constrain"));
    connect(tboxAddConstrainAction, SIGNAL(triggered()), this, SLOT(addConstrain()));
}


void MainWindow::createToolBar() {
    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    addConstrButton = new QToolButton;
    addConstrButton->setDefaultAction(toolbarAddConstrAction);

    calcConstrainsButton = new QToolButton;
    calcConstrainsButton->setDefaultAction(toolbarCalcConstrAction);

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(sceneScaleCombo);
    pointerToolbar->addWidget(addConstrButton);
    pointerToolbar->addWidget(calcConstrainsButton);
}


void MainWindow::createMenus() {
    // file menu entry
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}


void MainWindow::createToolBox() {
    QGridLayout *layout = new QGridLayout;

    QGroupBox* gbox = makeConstrainGroupBox();
    layout->addWidget(gbox, 0, 0);

    QToolButton *button = new QToolButton;
    button->setDefaultAction(tboxAddConstrainAction);
    layout->addWidget(button);
    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(200);
    toolBox->addItem(itemWidget, tr("Constrain Addition"));
}


QGroupBox* MainWindow::makeConstrainGroupBox() {
    QGroupBox* box = new QGroupBox(tr("Constrain parameters"));
    QLabel* typeLabel = new QLabel(tr("Constrain type"));

    constrainTypeCombo = new QComboBox;
    QStringList types;
    types << tr("one") << tr("two") << tr("three");  // <-- only for PoC. After testing replace it with right types!
    constrainTypeCombo->addItems(types);

    QDoubleValidator *valid = new QDoubleValidator(0.0, qInf(), 2, this);
    valid->setNotation(QDoubleValidator::StandardNotation);

    QLabel *val1Label = new QLabel(tr("Value1"));
    constrParam1SBox = new QDoubleSpinBox;

    QLabel *val2Label = new QLabel(tr("Value2"));
    constrParam2SBox = new QDoubleSpinBox;

    QGridLayout *localLayout = new QGridLayout;
    localLayout->addWidget(typeLabel, 0, 0);
    localLayout->addWidget(constrainTypeCombo, 0, 1);
    localLayout->addWidget(val1Label, 1, 0);
    localLayout->addWidget(constrParam1SBox, 1, 1);
    localLayout->addWidget(val2Label, 2, 0);
    localLayout->addWidget(constrParam2SBox, 2, 1);

    box->setLayout(localLayout);
    return box;
}

/********************
 * SLOTS impl. section
 *******************/

void MainWindow::openFile() {
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open PCB File"), ".", tr("PCB files(*.pcb)"));
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About PatWizard"),
                       tr("<b>PatWizard</b> is the bad example of C++ code."));
}


void MainWindow::sceneScaleChanged(const QString &scale) {
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::applyAddConstrMode(bool checked) {
    qDebug() << "applyAddConstrMode::" << checked;
    if (checked) {
        userMode = addConstrainMode;
    } else {
        userMode = usualMode;
    }
    //drawCircuit(); // <-- here? really?
}

void MainWindow::calculateConstrains()
{
    qDebug() << "calculateConstrains()";
    if (calcPending) {
        qDebug() << "calculation is already pending!";
        QMessageBox msgBox;
        msgBox.setText("Calculation is already pending!");
        msgBox.exec();
        return;
    }
    //commented due to incomplete implementation of GemetrySolver.
    //uncomment once it's implemented and tested.
    //QFuture<bool> future = QConcurrent::run(solver->RunSolver, objects);
    //QObject::connect(calculationWatcher, SIGNAL(finished()), this, SLOT(calcFinished()));
    //watcher.setFuture(future);
    calcPending = true;
    QFuture<bool> future = QtConcurrent::run(sleepy);
    connect(&calculationWatcher, SIGNAL(finished()), this, SLOT(calcFinished()));
    calculationWatcher.setFuture(future);
}

void MainWindow::calcFinished() {
    qDebug() << "calc finished";
    bool result = calculationWatcher.future().result();
    qDebug() << "result is " << result;
}

void MainWindow::addConstrain() {
    qDebug() << "addConstrain()";
    // err detection
    if (userMode != addConstrainMode) {
        qDebug() << "[diag] addConstrain:: userMode is invalid, no addition should be done";
        QMessageBox errBox;
        errBox.setText("Cannot add constrain with inactive AddConstrainMode");
        errBox.exec();
        return;
    }

    QString type = constrainTypeCombo->currentText();
    qDebug() << "addConstrain::" << type;
    double val1 = constrParam1SBox->value();
    double val2 = constrParam2SBox->value();

    qDebug() << "val1: " << val1 << "; val2 = " << val2 << ";";

    status->showMessage("add Constrain isn't complete!", 5000);
}
/*
 * SLOTS impl. END
 */

bool sleepy() {
    QThread::sleep(5); // sleep for 5 seconds;
    return false;
}


void calcArcAngles(double center_x, double center_y,
                   double x1, double y1,
                   double x2, double y2,
                   double& start_angle, double& end_angle,
                   bool cw)
{
    auto getVectMul = [center_x, center_y](double x1, double y1, double x2, double y2) {
        return (x1 - center_x) * (y2 - center_y) - (x2 - center_x) * (y1 - center_y);
    };
    auto getVectLength = [center_x, center_y](double x, double y) {
        return qSqrt(qPow(x - center_x, 2) + qPow(y - center_y, 2));
    };
    auto calcAngle = [center_x, center_y, getVectMul, getVectLength](double x, double y) {
        double vect_mul = getVectMul(center_x + 1, center_y, x, y);
        double angle = qAsin(vect_mul / getVectLength(x, y));
        if (vect_mul < 0) {
            angle = 360.0 - angle;
        } else if (vect_mul == 0 && x < center_x) {
            angle = 180.0;
        }
        return angle;
    };

    double vect_mul = getVectMul(x1, y1, x2, y2);

    start_angle = calcAngle(x1, y1);
    end_angle = calcAngle(x2, y2);

    if (vect_mul > 0 && cw) {
        qSwap(start_angle, end_angle);
    } else if (vect_mul == 0) {

    }
}

void MainWindow::drawCircuit() {
    const double SHIFT = 100;
    double min_x, min_y, max_x, max_y;

    if (objects.length() == 0)
        return;

    min_x = max_x = objects[0]->get_image()[0].x;
    min_y = max_y = objects[0]->get_image()[0].y;

    const double UNDEF = min_x - SHIFT - 10;

    foreach (GrObject* obj, objects) {
        foreach (GrShape shape, obj->get_image()) {
            min_x = qMin(min_x, shape.x);
            min_y = qMin(min_y, shape.y);
            max_x = qMax(max_x, shape.x);
            max_y = qMax(max_y, shape.y);
        }
    }

    scene->clear();
    scene->setSceneRect(QRectF(0, 0, max_x - min_x + 2 * SHIFT, max_y - min_y + 2 * SHIFT));

    auto getSceneX = [min_x, SHIFT](double x){ return x - min_x + SHIFT; };
    auto getSceneY = [max_y, SHIFT](double y){ return qAbs(y - max_y) + SHIFT; };
    auto getDistance = [](double x, double y, double x2, double y2) {
        return qSqrt(qPow(x - x2, 2) + qPow(y - y2, 2));
    };

    foreach (GrObject* obj, objects) {
        double x, y;
        double ac_x = UNDEF, ac_y = UNDEF;
        double ac_x2 = UNDEF, ac_y2 = UNDEF;
        GrShape::Type prev_type;

        foreach (GrShape shape, obj->get_image()) {
            switch (shape.type) {
            
            case GrShape::MoveTo:
                x = shape.x;
                y = shape.y;
                break;
            
            case GrShape::LineTo:
                if (!shape.options && GrShape::Hidden) {
                    WizardLineItem *item = new WizardLineItem(getSceneX(x),
                        getSceneY(y), getSceneX(shape.x), getSceneY(shape.y));
                    scene->addItem(item);
                }
                x = shape.x;
                y = shape.y;
                break;

            case GrShape::ArcCenter:
                ac_x = shape.x;
                ac_y = shape.y;
                break;

            case GrShape::ArcCenter2:
                ac_x2 = shape.x;
                ac_y2 = shape.y;
                break;
            
            case GrShape::ArcTo:
                if (!shape.options && GrShape::Hidden) {
                    double center_x, center_y;
                    double width, height;
                    double angle;
                    double start_arc, end_arc;
                    bool is_circle = ac_x2 == UNDEF;

                    center_x = is_circle ? ac_x : ac_x + (ac_x2 - ac_x) / 2;
                    center_y = is_circle ? ac_y : ac_y + (ac_y2 - ac_y) / 2;

                    if (is_circle) {
                        height = width = getDistance(x, y, center_x, center_y);
                        angle = 0.0;
                    } else {
                        width = getDistance(x, y, center_x, center_y)
                                + getDistance(shape.x, shape.y, center_x, center_y);
                        width /= 2;

                    }

                    if ((shape.options && GrShape::FullCircle)
                        || (shape.options && GrShape::ArcIsEllips)) {
                        start_arc = 0.0;
                        end_arc = 360.0;
                    } else {
                        calcArcAngles(center_x, center_y, x, y, shape.x, shape.y,
                                      start_arc, end_arc, shape.options && GrShape::ArcCW);
                    }


                    WizardArcItem* item = new WizardArcItem(x, y, x, x);
                    item->setStartAngle(x);
                    item->setSpanAngle(x);
                    scene->addItem(item);
                }
                x = shape.x;
                y = shape.y;
                ac_x = ac_x2 = ac_y = ac_y2 = UNDEF;
                break;
            
            case GrShape::Text:
                if (!shape.options && GrShape::Hidden) {
                    QGraphicsTextItem * io = new QGraphicsTextItem;
                    io->setPos(getSceneX(shape.x), getSceneY(shape.y));
                    io->setPlainText(shape.text);
                    scene->addItem(io);
                }

            case GrShape::ClosePath:
                if (prev_type == GrShape::MoveTo
                    && !shape.options && GrShape::Hidden)
                {
                    WizardPointItem * item = new WizardPointItem(getSceneX(shape.x),
                                                                 getSceneY(shape.y));
                    scene->addItem(item);
                }
                break;
            }
            prev_type = shape.type;
        }
    }
}
