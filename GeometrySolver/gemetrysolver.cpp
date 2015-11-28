#include "gemetrysolver.h"

QVector<QVector <delta> > GemetrySolver::RunSolver (QVector <GrObject> Shapes){
    QVector<QVector <delta> > local_delta;

    //Initializing class fields


    //Select micro in macro
    for (int i = 0; i < Shapes.size(); ++i)
    {
        GrObject shape = Shapes.at(i);
        vector_of_shapes = shape.get_image();
        //For current micro obkect in macro object select constrain
        //Need to add search of fix points.
        for (int j = 0; j < shape.get_constrains().size(); ++j)
        {
             Constrain constr = shape.get_constrains().at(j);
             if (ConstrainChecker(constr)){
                 //return leaf
             }
             else
             {
                 //Invest in us
                 //local_delta << ShiftSolver(constr);//several variants of possible positions of obj
             }
        }
    }
    return local_delta;

}


    bool GemetrySolver::ConstrainChecker(Constrain constr){
        double current_dist = 0;
        double A1, B1, C1, A2, B2, C2, yH1, xH1;
        //Check distance between points
        //Find the position of this element and next item in qvector is center
        GrShape center1 = vector_of_shapes.at(vector_of_shapes.indexOf(*constr.obj1)+1);
        GrShape center2 = vector_of_shapes.at(vector_of_shapes.indexOf(*constr.obj2)+1);
        double rad1, rad2, rad3, rad4;
        double angle1;
        double angle2;
        double angle3;
        double angle4;
        double angle5;
        double angle6;

        switch (constr.type) {
            case 1:
                //This point can not be shift, expose flag in true
                constr.obj1->fix = true;
                return true;
            case 2:
                //Check distance between points
                //Distance between points sqrt((x1-x2)^2 - (y1-y2)^2)
                current_dist = sqrt(pow(constr.obj1->x1 - constr.obj2->x1,2) + pow(constr.obj1->y1 - constr.obj2->y1, 2));
                break;
            case 3:
                //obj1 - point; obj2 - line
                //Check distance between point and line(normal)
                //Distance between point and line sqrt((x1-x2)^2 - (y1-y2)^2), where (x1,y1) - requered point and (x2,y2) - point of intersection point of line and normal
                //Сoefficients of equation of line
                A1 = constr.obj2->y2 - constr.obj2->y1;
                B1 = (-1)*(constr.obj2->x2 - constr.obj2->x1);
                C1 = (-1)*(constr.obj2->x1*(constr.obj2->y2 - constr.obj2->y1) + constr.obj2->y1*(constr.obj2->x2 - constr.obj2->x1));
                //Сoefficients of equation of normal to line
                A2 = B1;
                B2 = (-1)*A1;
                C2 = constr.obj1->x1*(-1)*B1 + constr.obj1->y1*A1;
                //Сoefficients of intersection point of line and normal
                yH1 = (A2*C1/A1 - C2)/(B2 - B1*A2/A1);
                xH1 = ((-1)*C1 - B1*yH1)/A1;
                current_dist = sqrt(pow(constr.obj1->x1 - xH1,2) + pow(constr.obj1->y1,2));
                break;
            case 4:
                //Check distance between point and ceneter of arc
                //Distance between points sqrt((x1-x2)^2 - (y1-y2)^2)
                current_dist = sqrt(pow(constr.obj1->x1 - constr.obj2->x1,2) + pow(constr.obj1->y1 - constr.obj2->y1, 2));
                break;
                //local_delta = arc_to_point(constr);
                break;
            case 5:
                //Check distance between line(Ax + Bx + C1 = 0) and line(Ax + By + C2 = 0)
                //Distance between line and line |C2- C1|/sqrt(A^2 + B^2)
                C1 = (-1)*(constr.obj1->x1*(constr.obj1->y2 - constr.obj1->y1) + constr.obj1->y1*(constr.obj1->x2 - constr.obj1->x1));
                C2 = (-1)*(constr.obj2->x1*(constr.obj2->y2 - constr.obj2->y1) + constr.obj2->y1*(constr.obj2->x2 - constr.obj2->x1));
                A1 = constr.obj2->y2 - constr.obj2->y1;
                B1 = (-1)*(constr.obj2->x2 - constr.obj2->x1);
                current_dist  = abs(C2 - C1)/sqrt(pow(A1,2) + pow(B1,2));
                break;
            case 6:
                //local_delta = angle_for_line(constr);
                current_dist = atan((constr.obj1->y2 - constr.obj1->y1)/(constr.obj1->x2-constr.obj1->x1));
                break;
            case 7:


                if (center1.type != ArcCenter || center2.type != ArcCenter)
                {
                    exit( -1);
                }
                else
                {
                    //Check radius for obj 1
                    rad1 = sqrt(pow(constr.obj1->x1 - center1.x1,2) + pow(constr.obj1->y1 - center1.y1, 2));
                    rad2 = sqrt(pow(constr.obj1->x1 - center1.x2,2) + pow(constr.obj1->y1 - center1.y2, 2));
                    //Check radius for obj 2
                    rad3 = sqrt(pow(constr.obj2->x1 - center2.x1,2) + pow(constr.obj2->y1 - center2.y1, 2));
                    rad4 = sqrt(pow(constr.obj2->x1 - center2.x2,2) + pow(constr.obj2->y1 - center2.y2, 2));
                    if ( rad1 != rad2 ||  rad3 != rad4 )
                        exit( -1);
                }
                //Distance between points sqrt((x1-x2)^2 - (y1-y2)^2)
                current_dist = sqrt(pow(center1.x1 - center2.x1,2) + pow(center1.y1 - center2.y1, 2));

                //Check crossing of line center-to-center and arcs
                angle1 = atan((center2.y1 - center1.y1)/(center2.x1-center1.x1));//arc1
                angle2 = atan((constr.obj1->y2 - center1.y1)/(constr.obj1->x2-center1.x1));
                angle3 = atan((constr.obj1->y1 - center1.y1)/(constr.obj1->x1-center1.x1));
                //For  arc2
                angle4 = atan((center1.y1 - center2.y1)/(center1.x1-center2.x1));
                angle5 = atan((constr.obj2->y2 - center2.y1)/(constr.obj2->x2-center2.x1));
                angle6 = atan((constr.obj2->y1 - center2.y1)/(constr.obj2->x1-center2.x1));
                //Assuming contr-clockwise angle numbering detect intersection
                if ( angle1 >= angle2 && angle1 <= angle3 && angle4 >= angle5 && angle4 <= angle6 )
                {
                    current_dist -= rad1;
                    current_dist -= rad3;
                }
                else if ( angle1 >= angle2 && angle1 <= angle3 )
                {
            current_dist = min( sqrt(pow(constr.obj1->x1 - center2.x1,2) + pow(constr.obj1->y1 - center2.y1, 2)),
                                sqrt(pow(constr.obj1->x2 - center2.x1,2) + pow(constr.obj1->y2 - center2.y1, 2)))
                                        - rad3;
                }
                else if ( angle4 >= angle5 && angle4 <= angle6 )
                {
            current_dist = min( sqrt(pow(constr.obj2->x1 - center1.x1,2) + pow(constr.obj2->y1 - center1.y1, 2)),
                                sqrt(pow(constr.obj2->x2 - center1.x1,2) + pow(constr.obj2->y2 - center1.y1, 2)))
                                        - rad1;
                }
                else
                {
                   double dis1 = min( sqrt(pow(constr.obj2->x1 - constr.obj1->x1,2) + pow(constr.obj2->y1 - constr.obj1->y1, 2)),
                                sqrt(pow(constr.obj2->x1 - constr.obj1->x2,2) + pow(constr.obj2->y1 - constr.obj1->y2, 2)));
                   double dis2 = min( sqrt(pow(constr.obj2->x2 - constr.obj1->x1,2) + pow(constr.obj2->y2 - constr.obj1->y1, 2)),
                                sqrt(pow(constr.obj2->x2 - constr.obj1->x2,2) + pow(constr.obj2->y2 - constr.obj1->y2, 2)));
                   current_dist = min( dis1, dis2);
                }
                //Check crossing of line center-to-center and arcs
                break;
            case 8:
                //Check angle in range for arc
                //Checks under next case if first object is angle to check and second is horizontal
                //TODO: make second object horizontal:
                //constr.obj2->x1 = O.x1 - R
                //constr.obj2->y1 = O.x1 - R
                break;
            case 9:
                //Check sweep in range for arc
                //if obj1 != obj2 for arc, it means that it is the sweep of the arc
                if ( constr.obj1->type == 3 && constr.obj2->type == 3 )/*ArcTo */
                {
                    //if obj1 == obj2 but for arc, it means that it is the angle of the arc
                    current_dist = acos((constr.obj1->x1-constr.obj1->x2)*(constr.obj2->x1-constr.obj2->x2)+
                                          (constr.obj1->y1-constr.obj1->y2)*(constr.obj2->y1-constr.obj2->y2)/
                                          sqrt(pow(constr.obj1->x1 - constr.obj2->x1,2) + pow(constr.obj1->y1 - constr.obj2->y1, 2)));
                }
                //local_delta = sweep_for_arc(constr);
                break;
            case 10:
                //local_delta = radius_for_arc(constr);
                //Calculates distance between obj1 - center of arc and obj2 - one of the points on arc.
                current_dist = sqrt(pow(constr.obj1->x1 - constr.obj2->x1,2) + pow(constr.obj1->y1 - constr.obj2->y1, 2));
                break;
            default:
               //It can be there your advertisiment
                break;
        }
        //if current distance between points is requered then do nothing and return true
        if (current_dist >= constr.options.param1 || current_dist <= constr.options.param2)
            return true;
        return false;
    }

    QVector <delta> GemetrySolver::point_to_point(Constrain constr){
        //Function will be called if constrains are not met, so there is no need to check it
                GrShape *point_1 = constr.obj1, *point_2 = constr.obj2;
                double start_required_dist = constr.options.param1, end_required_dist = constr.options.param2;
                double current_dist = 0;
                double shift =0;//
                QVector <delta> local_delta;
                delta local_shift;

                current_dist = sqrt(pow(point_1->x1 - point_2->x1,2) + pow(point_1->y1 - point_2->y1, 2));

                for (int i =0; i < 5; i++)//distance_p_p < start_required_dist || distance_p_p > end_required_dist)
                {
                    shift = (start_required_dist + i*(abs(end_required_dist - start_required_dist)/5)- current_dist)/2;
                    local_shift.obj = point_1;
                    local_shift.x = shift*(point_2->x1 - point_1->x1)/sqrt(pow((point_2->x1 - point_1->x1),2) + sqrt(pow((point_2->y1 - point_1->y1),2)));
                    local_shift.y = shift*(point_2->y1 - point_1->y1)/sqrt(pow((point_2->x1 - point_1->x1),2) + sqrt(pow((point_2->y1 - point_1->y1),2)));
                    local_delta.append(local_shift);
                    local_shift.obj = point_2;
                    local_shift.x = (-1)*shift*(point_2->x1 - point_1->x1)/sqrt(pow((point_2->x1 - point_1->x1),2) + sqrt(pow((point_2->y1 - point_1->y1),2)));
                    local_shift.y = (-1)*shift*(point_2->y1 - point_1->y1)/sqrt(pow((point_2->x1 - point_1->x1),2) + sqrt(pow((point_2->y1 - point_1->y1),2)));
                    local_delta.append(local_shift);
                }
                //Return several variants of solutions for each object
                return local_delta;
    }
