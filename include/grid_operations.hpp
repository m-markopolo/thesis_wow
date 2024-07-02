#ifndef GRID_OPERATIONS_HPP
#define GRID_OPERATIONS_HPP

#include <eigen3/Eigen/Dense>

void regenerate_2Dgrid( Eigen::MatrixXi & grid, double prob_trap ) ;
void modify_2Dgrid( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new ) ;

Eigen::MatrixXd get_distance_lookup_table(size_t grid_size);

#endif
