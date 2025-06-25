#include <iostream>
#include "simulated_annealing.h"

#include <string>
#include <fstream>
#include <sstream>

// Parameters of the simulated anealing method
const double ini_temp = 10'000 ;
const double cooling_rate = 0.995 ;
const double stop_temp = 1e-4 ;
const int max_iter = 5'000 ;

std::vector<std::vector<int>> read_matrix(const std::string& filename){
	std::ifstream infile(filename) ;
	std::string line ;
	std::vector<std::vector<int>> matrix ;
	
	std::vector<int> row ;
	while(std::getline(infile, line)){
		std::istringstream iss(line) ;
		row.clear() ;
		int num ;
		while(iss >> num){
			row.push_back(num) ;
		}
		matrix.push_back(row) ;
	}
	
	infile.close() ;
	return matrix ;
}

int main(){
	std::string file_path = "dataset/fri26_d.txt" ;
	
	simulated_annealing model(read_matrix(file_path), 42) ;
	
	model.solve(ini_temp, cooling_rate, stop_temp, max_iter) ;
	
	std::cout << "Best Cost: " << model.get_best_cost() << "\nBest Path: " ;
	for(int p: model.get_best_path()){
		std::cout << p << " " ;
	}
	std::cout << "0" << std::endl ;
	
	return 0 ;
}