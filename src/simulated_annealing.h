#pragma once

#include <random>
#include <vector>

// Solve TSP by the simulated anealing method
class simulated_annealing{
private:
	// distance matrix
	const std::vector<std::vector<int>> dist ;
	
	// Number of nodes(cities)
	const int n_nodes ;
	
	// Random generator
	std::mt19937 rng ;
	std::uniform_real_distribution<double> uni ;

	// Solution
	std::vector<int> best_path ;
	int best_cost ;
	
public:
	// Constructor: get the distance matrix and the seed of the random generator
	simulated_annealing(const std::vector<std::vector<int>>&, int) ;
	
	// Compute the cost of the argument path
	int path_cost(const std::vector<int>& ) ;
	
	// 2-opt method
	std::vector<int> swap_2opt(const std::vector<int>&) ;
	
	void solve(const double, const double, const double, const int) ;
	
	// Return the const reference of best_path, best_cost
	const int get_best_cost() const ;
	const std::vector<int>& get_best_path() const;
};
