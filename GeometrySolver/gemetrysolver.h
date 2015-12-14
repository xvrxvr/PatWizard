#ifndef GEMETRYSOLVER_H
#define GEMETRYSOLVER_H
#include "gr_object.h"
#include <cmath>
#include <QStack>
#include <QStack>

//Show difference between old and new coordinates of GrShape
struct delta{
    geom_index obj;//передавать индексы
    double x;
    double y;
};

struct rectangle{
    double left_x, left_y;
    double right_x, right_y;
    //Solutions if positive
    bool positive;
    geom_index host_shape;

    rectangle intercect( rectangle rvalue)
    {
        //if( left_x < rvalue.left_x ) if( right_x < rvalue.right_x ) if( left_y < rvalue.left_y ) if( right_y < rvalue.right_y )
        rectangle res;
        res.left_x = -1;
        res.left_y = -1;
        res.right_x = -1;
        res.right_y = -1;

        if( min( right_x, rvalue.right_x) > max( left_x, rvalue.left_x) && min( left_y, rvalue.left_y ) > max( right_y, rvalue.right_y) )
        {
            res.left_x = rvalue.left_x;
            res.left_y = left_y;
            res.right_x = right_x;
            res.right_y = rvalue.right_y;

        }

    return res;
    }

};

class GemetrySolver
{
public:
    QVector<GrShape> vector_of_shapes;
    QVector< QVector<delta> > solution;
    QVector< QVector<delta> > get_solution(){ return solution; }

    GemetrySolver();//возвращаем статус
    //добавить поле вектор дельт и для него написать get()
    bool RunSolver (QVector <GrObject> Shapes);

    //Check constrain. Input - constrain. Output - true or false.
    bool ConstrainChecker(Constrain constr);
    geom_index FindFixed(QVector< GrShape> vector_of_shapes);

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
