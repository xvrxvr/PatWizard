#include "gemetrysolver.h"

QVector<QVector <delta> > GemetrySolver::RunSolver (QVector <GrObject> Shapes){
    QVector<QVector <delta> > local_delta;
    //Select micro in macro
    for (int i = 0; i < Shapes.size(); ++i)
    {
        GrObject shape = Shapes.at(i);
        //For current micro obkect in macro object select constrain
        //Need to add search of fix points.
        for (int j = 0; j < shape.get_constrains().size(); ++j)
        {
             Constrain constr = shape.get_constrains().at(j);
             if (ConstrainChecker(constr)){
                 //return leaf
             }
             else
                 local_delta << ShiftSolver(constr);//several variants of possible positions of obj
             PreparePhase();
        }
    }
    CollectSolution();
    return local_delta;

}



