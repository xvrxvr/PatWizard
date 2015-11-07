#include "gemetrysolver.h"

GemetrySolver::GemetrySolver();
void GemetrySolver::point_to_point(GrShape &point_1, GrShape &point_2, double req_dist){
            double distance_p_p = 0;
            double middle_p_x = 0, middle_p_y = 0, delta =0;
            distance_p_p = sqrt(pow(point_1.x - point_2.x,2) + pow(point_1.y - point_2.y, 2));
            if (distance_p_p != req_dist)
            {
                middle_p_x = (point_1.x + point_2.x)/2;
                middle_p_y = (point_1.y + point_2.y)/2;
                delta = (req_dist-distance_p_p)/2;
                point_1.x = point_1.x + delta*(point_2.x - point_1.x)/(sqrt(pow(point_2.x - point_1.x),2) + sqrt(pow(point_2.y - point_1.y),2));
                point_1.y = point_1.y + delta*(point_2.y - point_1.y)/(sqrt(pow(point_2.x - point_1.x),2) + sqrt(pow(point_2.y - point_1.y),2));
                point_2.x = point_2.x - delta*(point_2.x - point_1.x)/(sqrt(pow(point_2.x - point_1.x),2) + sqrt(pow(point_2.y - point_1.y),2));
                point_2.y = point_2.y - delta*(point_2.y - point_1.y)/(sqrt(pow(point_2.x - point_1.x),2) + sqrt(pow(point_2.y - point_1.y),2));
            }
            return;
}

