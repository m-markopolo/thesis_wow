#ifndef GRID_OPERATIONS_HPP
#define GRID_OPERATIONS_HPP

#include "/usr/include/eigen3/Eigen/Dense"


void regenerate_2Dgrid( Eigen::MatrixXi & grid, double prob_trap ) ;
void modify_2Dgrid( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new ) ;


#endif
