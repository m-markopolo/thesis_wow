#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include "/usr/include/eigen3/Eigen/Dense"
#include <vector>
#include <random>
#include <numeric>

class Union_find{

private:

  int num_AEM = 4418;  
  std::mt19937 gen ;

  std::vector<int> m_labels ;
  std::vector<int> m_clust_size ;
  Eigen::MatrixXi m_grid ;
  
  void bound_cond( int idx_row, int idx_col, int & left, int & up );

  int uf_find( int x ) ;
  int uf_union ( int x , int y );	

public:

  Union_find(size_t grid_size) : gen(num_AEM ) {

    m_labels.resize( grid_size * grid_size / 2  ) ;
    m_clust_size.resize( grid_size * grid_size / 2 ,0   ) ;

    std::iota(m_labels.begin(), m_labels.end(), 0 ) ;

    m_grid = Eigen::MatrixXi{grid_size, grid_size} ;

  }

  
  std::vector<int> cluster_sizes() const {
    return m_clust_size ;
  }

  void clear_sizes(){
    std::fill(m_clust_size.begin(), m_clust_size.end(), 0 ) ;
    std::iota(m_labels.begin(), m_labels.end(), 0 ) ;
  }
  void replace_nodes_until_new_prob_is_reached( double prob_trap_old, double prob_trap_new ) ;
  void create_2Dgrid( double prob_trap ) ;

  int relabel_and_get_max_cluster_size();
  void hk();


};

#endif 
