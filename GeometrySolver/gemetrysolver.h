#ifndef GEMETRYSOLVER_H
#define GEMETRYSOLVER_H
#include "gr_object.h"
#include "math.h"

class GemetrySolver
{
public:
    GemetrySolver();
    void point_to_point(GrShape &point_1, GrShape &point_2, double req_dist);
    void pcoordinate_for_point(GrShape &point_1, double x, double y);
    void line_to_point(GrShape &line, GrShape &point, double req_dist);
    void art_to_point(GrShape &arc, GrShape &point, double req_dist);
    void line_to_line(GrShape &line, GrShape &line, double req_dist, double angle);
    void angle_for_line(GrShape &line, double angle);
    void arc_to_arc(GrShape &arc, GrShape &arc, double req_dist, double angle);
    void angle_for_arc(GrShape &line, double angle_1, double angle_2);
    void sweep_for_arc(GrShape &line, double sweep);
    void radius_for_arc(GrShape &line, double radius_1, double radius_2);


};

#endif // GEMETRYSOLVER_H
