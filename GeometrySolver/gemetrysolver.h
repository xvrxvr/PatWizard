#ifndef GEMETRYSOLVER_H
#define GEMETRYSOLVER_H
#include "gr_object.h"
#include <cmath>
//Show difference between old and new coordinates of GrShape
struct delta{
    GrShape *obj;//передавать индексы
    double x;
    double y;
};

class GemetrySolver
{
public:
    GemetrySolver();//возвращаем статус
    //добавить поле вектор дельт и для него написать get()
    QVector<QVector <delta> > RunSolver (QVector <GrObject> Shapes);

    //Check constrain. Input - constrain. Output - true or false.
    bool ConstrainChecker(Constrain constr);
    //Return several variants of possible placement of current objs.
    QVector <delta> ShiftSolver(Constrain constr);
    //Form tree of variants of shifts. Input - local_delta, pointer to tree struct. Output - pointer to finished tree.
    void PreparePhase();
    //Input - pointer to struct tree. Output  - QVector<QVector <delta> > (that's exactly solve of the problem)
    void CollectSolution();

    QVector <delta> point_to_point(Constrain constr);
    void coordinate_for_point(Constrain constr);//GrShape &point_1, double x, double y);
    void line_to_point(Constrain constr);//GrShape &line, GrShape &point, double req_dist);
    void arc_to_point(Constrain constr);//GrShape &arc, GrShape &point, double req_dist);
    void line_to_line(Constrain constr);//GrShape &line1, GrShape &line2, double req_dist, double angle);
    void angle_for_line(Constrain constr);//GrShape &line, double angle);
    void arc_to_arc(Constrain constr);//GrShape &arc1, GrShape &arc2, double req_dist, double angle);
    void angle_for_arc(Constrain constr);//GrShape &line, double angle_1, double angle_2);
    void sweep_for_arc(Constrain constr);//GrShape &line, double sweep);
    void radius_for_arc(Constrain constr);//GrShape &line, double radius_1, double radius_2);




};

#endif // GEMETRYSOLVER_H
