#include "simulated_annealing.h"

#include <cmath>
#include <algorithm>
#include <utility>

simulated_annealing::simulated_annealing(const std::vector<std::vector<int>>& dMatrix, int seed=42)
: dist(dMatrix), n_nodes(dMatrix.size()), uni(0.0, 1.0){
	rng.seed(seed) ;
}

int simulated_annealing::path_cost(const std::vector<int>& path){
	int cost = 0;
	for(int i=0; i<n_nodes-1; i++){
		cost += dist[path[i]][path[i+1]] ;
	}
	cost += dist[path[n_nodes-1]][path[0]] ;
	
	return cost ;
}

std::vector<int> simulated_annealing::swap_2opt(const std::vector<int>& path){
	std::vector<int> new_path(path) ;
	std::uniform_int_distribution<int> range(1, n_nodes-1) ;
	
	int i=range(rng), j = range(rng) ;
	if(i > j) std::swap(i, j) ;
	std::reverse(new_path.begin()+i, new_path.begin()+j+1) ;
	return new_path ;
}

const int simulated_annealing::get_best_cost() const{
	return best_cost ;
}

const std::vector<int>& simulated_annealing::get_best_path() const{
	return best_path ;
}

void simulated_annealing::solve(
	const double ini_temp = 10'000,
	const double cooling_rate = 0.995,
	const double stop_temp = 1e-4,
	int max_iter = 5'000){
	
	// S = S_0
	std::vector<int> current_path(n_nodes) ;
	for(int i=0; i<n_nodes; ++i) current_path[i] = i ;
	
	std::shuffle(current_path.begin()+1, current_path.end(), rng) ;
	best_path = current_path ;
	
	// E = E(S)
	int current_cost = path_cost(current_path) ;
	best_cost = current_cost ;
	
	// T = T_0
	double T = ini_temp ;
	
	for(int iter=0; iter<max_iter; ++iter){		
		if(T <= stop_temp){
			break ;
		}
		
		std::vector<int> new_path = swap_2opt(current_path) ;
		int new_cost = path_cost(new_path) ;
		
		if(new_cost < current_cost ||
		   uni(rng) < std::exp( (current_cost - new_cost) / T )){
			current_path = std::move(new_path) ;
			current_cost = new_cost ;
			if(new_cost < best_cost){
				best_cost = new_cost ;
				best_path = current_path ;
			}
			
		}
		T *= cooling_rate ;
	}
}