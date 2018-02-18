/*
/ Program: qBot
/ File: q_learn.h
/ Author: Andrew Holman
/ Assignment: Final
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: December 13, 2017
/
/ Description: Header file for q_learn class
*/

#ifndef Q_LEARN_H
#define Q_LEARN_H

#include <vector>

#include "room.h"

class Q_Learn {
	public:
		Q_Learn();
		void test();
		void train(bool show);

	private:
		void print_help();
		void test_print();
		void print_rooms();
		void find_route(int goal);
		int random_state(int cur_state);
		int max_index(int state);
        void load_states();
		void initialize_matrices();
		void store_matrix(int iteration, int m);

		bool converged = false; //Flag for determining training convergence
        std::vector<Room> states; //Vector holding all the rooms (states) in the system

    	// Matrix indices represent M[to_state][from_state]
		// rather than the usual M[from_state][to_state]
		std::vector< std::vector<int> > q_matrix; // 2d vector for q values
		std::vector< std::vector<int> > r_matrix; // 2d vector for r values
};

#endif
