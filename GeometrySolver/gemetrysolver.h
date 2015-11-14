#ifndef GEMETRYSOLVER_H
#define GEMETRYSOLVER_H
#include "gr_object.h"
#include <cmath>
//Show difference between old and new coordinates of GrShape
struct delta{
    GrShape obj;
    double x;
    double y;
};

class GemetrySolver
{
public:
    GemetrySolver();
    QVector<QVector <delta> > RunSolver (QVector <GrObject> Shapes){
        //Select micro in macro
        for (int i = 0; i < Shapes.size(); ++i)
        {
            GrObject shape = Shapes.at(i);
            //For current micro obkect in macro object select constrain
            for (int j = 0; j < shape.get_constrains().size(); ++j)
            {
                 Constrain constr = shape.get_constrains().at(j);
                 //Detect type of constrain and solve it
                 switch (constr.type) {
                 case 1:
                     coordinate_for_point(constr);
                     break;
                 case 2:
                     point_to_point(constr);
                     break;
                 case 3:
                     line_to_point(constr);
                     break;
                 case 4:
                     arc_to_point(constr);
                     break;
                 case 5:
                     line_to_line(constr);
                     break;
                 case 6:
                     angle_for_line(constr);
                     break;
                 case 7:
                     arc_to_arc(constr);
                     break;
                 case 8:
                     angle_for_arc(constr);
                     break;
                 case 9:
                     sweep_for_arc(constr);
                     break;
                 case 10:
                     radius_for_arc(constr);
                     break;
                 default:
                    //It can be there your advertisiment
                     break;
                 }
            }


        }

    }
    QVector <delta> point_to_point(Constrain constr){
                GrShape point_1 = constr.obj1, point_2 = constr.obj2;
                double start_required_dist = constr.options.param1, end_required_dist = constr.options.param2;
                double current_dist = 0;
                double shift =0;//
                QVector <delta> local_delta = *new QVector <delta>;
                delta local_shift;

                current_dist = sqrt(pow(point_1.x - point_2.x,2) + pow(point_1.y - point_2.y, 2));

                //if current distance between points is requered then do nothing
                if (current_dist >= start_required_dist || current_dist <= end_required_dist)
                    return local_delta;

                for (int i =0; i < 5; i++)//distance_p_p < start_required_dist || distance_p_p > end_required_dist)
                {
                    shift = (start_required_dist + i*(abs(end_required_dist - start_required_dist)/5)- current_dist)/2;
                    local_shift.obj = point_1;
                    local_shift.x = shift*(point_2.x - point_1.x)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_shift.y = shift*(point_2.y - point_1.y)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_delta.append(local_shift);
                    local_shift.obj = point_2;
                    local_shift.x = (-1)*shift*(point_2.x - point_1.x)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_shift.y = (-1)*shift*(point_2.y - point_1.y)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_delta.append(local_shift);
                }
                //Return several variants of solutions for each object
                return local_delta;
    }
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
