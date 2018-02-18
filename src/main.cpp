/*
/ Program: qBot
/ File: main.cpp
/ Author: Andrew Holman
/ Assignment: Final
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: December 14, 2017
/
/ Description: Main file for qBot program. This file is the entry point for the program.
*/

#include <iostream>

#include "settings.h"
#include "q_learn.h"

int main(int argc, char **argv) {
	std::string arg;
	bool show_train = false;

	//Parse arguments
	if (argc > 1) {
		arg = std::string(argv[1]);

		//Print training data while training
		if (arg == "-t") {
			show_train = true;
		} else {
			std::cerr << "Error: invalid command line argument\n";
			std::cerr << "System Exiting...\n";
			exit(1);
		}
	}

	//Train and test q learning bot
	Q_Learn q;
	q.train(show_train);
	q.test();
	return 1;
}
