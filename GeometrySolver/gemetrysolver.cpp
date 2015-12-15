#include "gemetrysolver.h"
#include "graph.h"

geom_index GemetrySolver::FindFixed(QVector< GrShape> vector_of_shapes)
{
    geom_index res = 0;
    for ( int i = 0 ; i < vector_of_shapes.length(); ++i)
    {
       if( vector_of_shapes.at(i).options == GrShape::FixedPoint)
           return i;
       if( vector_of_shapes.at(i).type == GrShape::MoveTo)
           res = i;
    }
    return res;
}

bool GemetrySolver::RunSolver (QVector <GrObject> gr_objects){
    QVector<QVector <delta> > local_delta;
    QVector< rectangle > possible_solutions;

    //Select micro in macro
    for (int i = 0; i < gr_objects.size(); ++i)
    {
        GrObject gr_object = gr_objects.at(i);
        vector_of_shapes = gr_object.get_image();
        //Fullfill the graph
        Graph graph(vector_of_shapes.length());

        for (int j = 0; j < gr_object.get_constrains().size(); ++j)
        {
           Constrain constr = gr_object.get_constrains().at(j);
           graph.addEdge(constr.obj1, constr.obj2, constr);
        }

        //DFS for preparing starting searching areas
        geom_index fixed_point = FindFixed( vector_of_shapes);
        graph.DFN(fixed_point);
        list< list<geom_index> > allCycles = graph.cycleSearch();
        list<geom_index> globalCycle;
        for ( int i = 0 ; i < vector_of_shapes.length(); ++i)
        {
           globalCycle.push_back(i);
        }
        Tree GlobalTree(globalCycle);
        GlobalTree.BuildTreeCycle(allCycles);



//        QVector< Constrain > miserable_constr;
        //For current micro obkect in macro object select constrain
        //Need to add search of fix points.
//        for (int j = 0; j < gr_object.get_constrains().size(); ++j)
//        {
//             Constrain constr = gr_object.get_constrains().at(j);

//             if ( constr.obj1 == fixed_point || constr.obj2 == fixed_point )
//             {
//                 geom_index constr_fixed = (constr.obj1 == fixed_point) ? constr.obj1 : constr.obj2;
//                 geom_index host_shape = (constr.obj1 =! fixed_point) ? constr.obj1 : constr.obj2;
//                 rectangle leaf_soulutions[2];
//                 if ( constr.type == Constrain::PointToPoint )
//                 {
//                    //Linear interpolation of circle around fixed point
//                    leaf_soulutions[1].left_x = vector_of_shapes.at(constr_fixed).x - constr.options.param1;
//                    leaf_soulutions[1].left_y = vector_of_shapes.at(constr_fixed).y - constr.options.param1;

//                    leaf_soulutions[1].right_x = vector_of_shapes.at(constr_fixed).x - constr.options.param1;
//                    leaf_soulutions[1].right_y = vector_of_shapes.at(constr_fixed).y - constr.options.param1;

//                    leaf_soulutions[1].positive = true;
//                    leaf_soulutions[1].host_shape = host_shape;
// //No solutions here
//                    leaf_soulutions[2].left_x = vector_of_shapes.at(constr_fixed).x - constr.options.param2;
//                    leaf_soulutions[2].left_y = vector_of_shapes.at(constr_fixed).y - constr.options.param2;

//                    leaf_soulutions[2].right_x = vector_of_shapes.at(constr_fixed).x - constr.options.param2;
//                    leaf_soulutions[2].right_y = vector_of_shapes.at(constr_fixed).y - constr.options.param2;

//            leaf_soulutions[1].positive = false;
//            leaf_soulutions[1].host_shape = host_shape;
//                 }
//                 if( host_shape != GrShape::FixedPoint)
//                 {
//             possible_solutions.append(leaf_soulutions[1]);
//             possible_solutions.append(leaf_soulutions[2]);
//                 }
//                 else
//                 {
//                     //Object of non-fixed point and artificial rectangle for solution
//                     GrShape h = vector_of_shapes.at(host_shape);
//                     rectangle artif_point = {h.x,h.y,h.x,h.y,true,host_shape};
//                     rectangle p_intersection = artif_point.intercect(leaf_soulutions[1]);
//                     rectangle n_intersection = artif_point.intercect(leaf_soulutions[2]);
//                     if ( p_intersection.left_x == -1 || n_intersection.left_x != -1 )
//                     {
//                         return false;
//                     }
//                     else
//                     {
//                         possible_solutions.append(artif_point);
//                     }
//                 }
//             }
//             else
//             {
//                 //Constrains for standalone processing
//                 //miserable_constr.append(constr);
//             }
//        }/*Constraints cycle*/
        //for( int j = 0 ; j <= miserable_constr.length() ; ++j )
        {
            //if ( vector_of_shapes.at(constr.obj1) )
        }
    }/*GrShapes cycle*/

    /*solution;*/// = local_delta;
    return true;
}


    bool GemetrySolver::ConstrainChecker(Constrain constr){
        double current_dist = 0;
        double A1, B1, C1, A2, B2, C2, yH1, xH1;
        //Check distance between points
        //Find the position of this element and next item in qvector is center
        GrShape obj1 = vector_of_shapes.at(constr.obj1), obj2 = vector_of_shapes.at(constr.obj2);
        GrShape next1 = vector_of_shapes.at(constr.obj1+1);//do not find, rather use index
        GrShape next2 = vector_of_shapes.at(constr.obj2+1);
        double rad1, rad2, rad3, rad4;
        double angle1;
        double angle2;
        double angle3;
        double angle4;
        double angle5;
        double angle6;
        GrShape end_of_line = vector_of_shapes.at(constr.obj2 + 1);

        switch (constr.type) {
            case Constrain::PointCoord:
                //This point can not be shift, expose flag in true
                obj1.fix = true;//TODO: сделать новую структуру с фиксированными точками
                return true;
            case Constrain::PointToPoint:
                //Check distance between points
                //Distance between points sqrt((x1-x2)^2 - (y1-y2)^2)
                current_dist = sqrt(pow(obj1.x - obj2.x,2) + pow(obj1.y - obj2.y, 2));
                break;
            case Constrain::LineToPoint:
                //obj1 - point; obj2 - line
                //Check distance between point and line(normal)
                //Distance between point and line sqrt((x1-x2)^2 - (y1-y2)^2), where (x1,y1) - requered point and (x2,y2) - point of intersection point of line and normal
                //Сoefficients of equation of line

                A1 = next2.y - obj2.y;
                B1 = (-1)*(next2.x - obj2.x);
                C1 = (-1)*(obj2.x*(end_of_line.y - obj2.y) + obj2.y*(next2.x - obj2.x));
                //Сoefficients of equation of normal to line
                A2 = B1;
                B2 = (-1)*A1;
                C2 = obj1.x*(-1)*B1 + obj1.y*A1;
                //Сoefficients of intersection point of line and normal
                yH1 = (A2*C1/A1 - C2)/(B2 - B1*A2/A1);
                xH1 = ((-1)*C1 - B1*yH1)/A1;
                current_dist = sqrt(pow(obj1.x - xH1,2) + pow(obj1.y,2));
                break;
            case Constrain::ArcToPoint:
                //Check distance between point and ceneter of arc
                //Distance between points sqrt((x1-x2)^2 - (y1-y2)^2)
                current_dist = sqrt(pow(obj1.x - obj2.x,2) + pow(obj1.y - obj2.y, 2));
                break;
                //local_delta = arc_to_point(constr);
                break;
            case Constrain::LineToLine:
                //Check distance between line(Ax + Bx + C1 = 0) and line(Ax + By + C2 = 0)
                //Distance between line and line |C2- C1|/sqrt(A^2 + B^2)
                C1 = (-1)*(obj1.x*(next1.y - obj1.y) + obj1.y*(next1.x - obj1.x));
                C2 = (-1)*(obj2.x*(next1.y - obj2.y) + obj2.y*(next2.x - obj2.x));
                A1 = next2.y - obj2.y;
                B1 = (-1)*(next2.x - obj2.x);
                current_dist  = abs(C2 - C1)/sqrt(pow(A1,2) + pow(B1,2));
                break;
            case Constrain::LineAngle:
                //local_delta = angle_for_line(constr);
                current_dist = atan((next1.y - obj1.y)/(next1.x-obj1.x));
                break;
            case Constrain::ArcToArc:


                if (next1.type != GrShape::ArcCenter || next2.type != GrShape::ArcCenter)
                {
                    exit( -1);
                }
                else
                {
                    GrShape end_of_arc1 = vector_of_shapes.at(constr.obj1+2);
                    GrShape end_of_arc2 = vector_of_shapes.at(constr.obj2+2);
                    //Check radius for obj 1
                    rad1 = sqrt(pow(obj1.x - next1.x,2) + pow(obj1.y - next1.y, 2));
                    rad2 = sqrt(pow(obj1.x - end_of_arc1.x,2) + pow(obj1.y - end_of_arc1.y, 2));
                    //Check radius for obj 2
                    rad3 = sqrt(pow(obj2.x - next2.x,2) + pow(obj2.y - next2.y, 2));
                    rad4 = sqrt(pow(obj2.x - end_of_arc2.x,2) + pow(obj2.y - end_of_arc2.y, 2));
                    if ( rad1 != rad2 ||  rad3 != rad4 )
                        exit( -1);
                }
                //Distance between points sqrt((x1-x2)^2 - (y1-y2)^2)
                current_dist = sqrt(pow(next1.x - next2.x,2) + pow(next1.y - next2.y, 2));

                //Check crossing of line center-to-center and arcs
                angle1 = atan((next2.y - next1.y)/(next2.x-next1.x));//arc1
                angle2 = atan((next1.y - next1.y)/(next1.x-next1.x));
                angle3 = atan((obj1.y - next1.y)/(obj1.x-next1.x));
                //For  arc2
                angle4 = atan((next1.y - next2.y)/(next1.x-next2.x));
                angle5 = atan((next2.y - next2.y)/(next2.x-next2.x));
                angle6 = atan((obj2.y - next2.y)/(obj2.x-next2.x));
                //Assuming contr-clockwise angle numbering detect intersection
                if ( angle1 >= angle2 && angle1 <= angle3 && angle4 >= angle5 && angle4 <= angle6 )
                {
                    current_dist -= rad1;
                    current_dist -= rad3;
                }
                else if ( angle1 >= angle2 && angle1 <= angle3 )
                {
            current_dist = min( sqrt(pow(obj1.x - next2.x,2) + pow(obj1.y - next2.y, 2)),
                                sqrt(pow(next1.x - next2.x,2) + pow(next1.y - next2.y, 2)))
                                        - rad3;
                }
                else if ( angle4 >= angle5 && angle4 <= angle6 )
                {
            current_dist = min( sqrt(pow(obj2.x - next1.x,2) + pow(obj2.y - next1.y, 2)),
                                sqrt(pow(next2.x - next1.x,2) + pow(next2.y - next1.y, 2)))
                                        - rad1;
                }
                else
                {
                   double dis1 = min( sqrt(pow(obj2.x - obj1.x,2) + pow(obj2.y - obj1.y, 2)),
                                sqrt(pow(obj2.x - next1.x,2) + pow(obj2.y - next1.y, 2)));
                   double dis2 = min( sqrt(pow(next2.x - obj1.x,2) + pow(next2.y - obj1.y, 2)),
                                sqrt(pow(next2.x - next1.x,2) + pow(next2.y - next1.y, 2)));
                   current_dist = min( dis1, dis2);
                }
                //Check crossing of line center-to-center and arcs
                break;
            case Constrain::ArcAngle:
                //Check angle in range for arc
                //Checks under next case if first object is angle to check and second is horizontal
                //TODO: make second object horizontal:
                //constr.obj2->x1 = O.x1 - R
                //constr.obj2->y1 = O.x1 - R
            case Constrain::ArcSweep:
                //Check sweep in range for arc
                //if obj1 != obj2 for arc, it means that it is the sweep of the arc
                if ( obj1.type == 3 && obj2.type == 3 )/*ArcTo */
                {
                    //if obj1 == obj2 but for arc, it means that it is the angle of the arc
                    current_dist = acos((obj1.x-next1.x)*(obj2.x-next2.x)+
                                          (obj1.y-next1.y)*(obj2.y-next2.y)/
                                          sqrt(pow(obj1.x - obj2.x,2) + pow(obj1.y - obj2.y, 2)));
                }
                //local_delta = sweep_for_arc(constr);
                break;
            case Constrain::ArcRadius:
                //local_delta = radius_for_arc(constr);
                //Calculates distance between obj1 - center of arc and obj2 - one of the points on arc.
                current_dist = sqrt(pow(obj1.x - obj2.x,2) + pow(obj1.y - obj2.y, 2));
                break;
            default:
                return false;
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
                GrShape point_1 = vector_of_shapes.at(constr.obj1), point_2 = vector_of_shapes.at(constr.obj2);
                double start_required_dist = constr.options.param1, end_required_dist = constr.options.param2;
                double current_dist = 0;
                double shift =0;//
                QVector <delta> local_delta;
                delta local_shift;

                current_dist = sqrt(pow(point_1.x - point_2.x,2) + pow(point_1.y - point_2.y, 2));

                for (int i =0; i < 5; i++)//distance_p_p < start_required_dist || distance_p_p > end_required_dist)
                {
                    shift = (start_required_dist + i*(abs(end_required_dist - start_required_dist)/5)- current_dist)/2;
                    local_shift.obj = constr.obj1;
                    local_shift.x = shift*(point_2.x - point_1.x)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_shift.y = shift*(point_2.y - point_1.y)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_delta.append(local_shift);
                    local_shift.obj = constr.obj2;
                    local_shift.x = (-1)*shift*(point_2.x - point_1.x)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_shift.y = (-1)*shift*(point_2.y - point_1.y)/sqrt(pow((point_2.x - point_1.x),2) + sqrt(pow((point_2.y - point_1.y),2)));
                    local_delta.append(local_shift);
                }
                //Return several variants of solutions for each object
                return local_delta;
    }
