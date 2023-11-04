#include "/usr/include/eigen3/Eigen/Dense"
#include <vector>


int uf_find( int x, std::vector<int> & labels ) ;
int uf_union ( int x , int y, std::vector<int> & labels );	
int relabel ( Eigen::MatrixXi & grid, std::vector<int> & labels, std::vector<int> & clust_size  );

void bound_cond( int idx_row, int idx_col, int & left, int & up, Eigen::MatrixXi & grid );
void hk ( std::vector<int> & labels, Eigen::MatrixXi & grid );
void label_reset( std::vector<int> & labels );
