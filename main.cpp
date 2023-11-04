#include "grid_operations.hpp"
#include "union_find.hpp"

#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <unistd.h>
#include <omp.h>


void write_results( std::string filename , std::vector<double> const & results ){

  std::ofstream fp ( filename ) ; 

  for ( size_t idx_write = 0 ; idx_write < results.size();  ++idx_write ){

    char const * ending = (  idx_write == results.size() -1 ) ? "" : "," ;
    fp << results[idx_write] << ending ;
  }
}



std::vector<double> get_probabilities(){
  return std::vector<double>{ 
    0.2,
    0.3,
    0.4,
    0.5,
    0.55,
    0.56,
    0.57,
    0.58,
    0.585,
    0.59, 
    0.595,
    0.6,
    0.615,
    0.61,
    0.62,
    0.63,
    0.64,
    0.65,
    0.7,
    0.8,
    0.9
  } ; 
}

struct Cluster_results {
private:
  size_t m_num_labels ;

public:
  Cluster_results(size_t num_labels) : m_num_labels(num_labels){

    Iav.resize(m_num_labels, 0) ;
    Iav_prime.resize(m_num_labels, 0) ;
    pmax.resize(m_num_labels, 0) ;
  }
  std::vector<double>	Iav ;
  std::vector<double>	Iav_prime ;
  std::vector<double>	pmax ;

};

struct Cluster_data{

private:
  size_t m_num_labels ;

public:

  Cluster_data(size_t num_labels) : m_num_labels(num_labels){
    labels.resize ( m_num_labels, 0) ;
    sizes.resize( m_num_labels, 0 ) ;
  } ;

  std::vector<int> labels ;
  std::vector<int> sizes;
  size_t max_cluster_size = 0 ;
};

Cluster_results update_results( Cluster_data const & clust_data, Cluster_results & results,
                               size_t idx_prob, double num_1){


  for( auto x : clust_data.sizes ){

    size_t cluster_size = x ;
    double normalized_cluster_size = ( cluster_size * cluster_size  ) /  num_1    ; 

    results.Iav[ idx_prob ] += normalized_cluster_size ;

    results.Iav_prime[ idx_prob ] +=  (cluster_size == clust_data.max_cluster_size ) ? 
      0 : normalized_cluster_size   ;

    results.pmax[ idx_prob ] +=  clust_data.max_cluster_size /  num_1  ; 

  }
    return results ; 
}

  void get_results(size_t grid_size, size_t num_rep ){

    size_t num_labels = grid_size * grid_size / 2  ; 

    Eigen::MatrixXi grid( grid_size , grid_size ) ; 
    grid.setZero() ; 

    std::vector<double> p_val = get_probabilities() ;

    Cluster_data clust_data(num_labels) ; 
    Cluster_results results(p_val.size()) ;

    for ( size_t idx_rep = 0 ; idx_rep < num_rep ; ++idx_rep ){

      create_2Dgrid( grid, p_val.back()) ;

      for ( size_t idx_prob = p_val.size() - 1 ; idx_prob > 0 ; --idx_prob ){

        double prob_old = p_val[idx_prob] ;
        double prob_new = p_val[idx_prob - 1 ] ;

        double num_1 =  prob_new * grid_size * grid_size  * num_rep  ;  


        modify_2Dgrid( grid, prob_old, prob_new ) ;

//        std::iota(clust_data.labels.begin(), clust_data.labels.end(), 0 ) ; 

        hk( clust_data.labels, grid) ;
        clust_data.max_cluster_size = relabel ( grid, clust_data.labels, clust_data.sizes  );

        results = update_results(clust_data, results, idx_prob, num_1)  ;

        std::fill( clust_data.sizes.begin(), clust_data.sizes.end(), 0 ) ; 
      }
    }

    write_results( "results/Iav.txt", results.Iav ) ;
    write_results( "results/Iav_prime.txt", results.Iav_prime ) ;
    write_results( "results/pmax.txt" , results.pmax ) ;
  }


  int main(){

    size_t grid_size = 100 ; 
    size_t num_rep = 10 ; 

    get_results(grid_size, num_rep );

  }
