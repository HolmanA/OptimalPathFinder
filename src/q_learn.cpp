/*
/ Program: qBot
/ File: q_learn.cpp
/ Author: Andrew Holman
/ Assignment: Final
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: December 14, 2017
/
/ Description: cpp file for Q_Learn class. This class defines a bot able to learn
/   optimal paths through Q-Learning.
*/

#include <iostream>
#include <fstream>
#include <set>
#include <queue>

#include "q_learn.h"
#include "settings.h"

// Constructor for Q Learn bot
Q_Learn::Q_Learn() {
    load_states();
    initialize_matrices();
}

// Main test function containing the loop that requests user input.
// This function handles user input and calls corresponding functions based on that input
void Q_Learn::test() {
    std::string user_input;

    print_rooms();
    print_help();

    // Main ui loop
    while (true) {
        // Get user input
        std::cout << "  Enter the index corresponding to the room you would like directions to: ";
        getline(std::cin, user_input);

        // Evaluate user input
        if (user_input == "list") {
            print_rooms();
        } else if (user_input == "exit") {
            exit(0);
        } else if (user_input == "help") {
            print_help();
        } else if (user_input == "all") {
            test_print();
        } else {
            std::unordered_map<std::string, int>::const_iterator room = room_numbers.find(user_input);
            if (room == room_numbers.end()) {
                std::cout << "  Room " << user_input << " Not Found!\n";
            } else {
                find_route(room->second);
            }
        }
    }
}

// Prints the optimal routes from the home room to all rooms in the system
void Q_Learn::test_print() {
    for (int i = 0; i < states.size(); i++) {
        find_route(i);
    }
}

// Prints help dialog
void Q_Learn::print_help() {
    std::cout << "\n==========================================================\n\n";
    std::cout << "                       Help Dialog                          \n";
    std::cout << "----------------------------------------------------------\n\n";
    std::cout << " Commands:\n";
    std::cout << "   'list' : Show room table\n";
    std::cout << "   'help' : Show help dialog\n";
    std::cout << "   'all' : Print the optimal route for all rooms\n";
    std::cout << "   'exit' : Exit program\n\n";
    std::cout << " How to Use:\n";
    std::cout << "   When prompted, enter the index corresponding to the room you would like directions to.\n";
    std::cout << "   If you would like some additional information, any of the four commands listed above can be entered instead of an index value.\n";
    std::cout << "\n==========================================================\n\n";
}

// Prints a table of all rooms in the system with their corresponding index values
// Dynamically pads table for visual allignment
void Q_Learn::print_rooms() {
    int table_width = 15; //Width of table; Does not include || table borders
    int col_width = (table_width / 2); //Width of columns in room table; used for padding calculations

    std::cout << "\n==========================================================\n\n";

    std::string table_title = "Room Table";

    // Double dash horizontal line
    std::cout << "  ";
    for (int i = 0; i < table_width + 4; i++) {
        std::cout << "=";
    }
    std::cout << "\n";

    // Table Header
    std::cout << "  ||";
    int left_padding = (table_width - table_title.size()) / 2;
    int right_padding = table_width - (table_title.size() + left_padding);

    for (int i = 0; i < left_padding; i++) {
        std::cout << " ";
    }

    std::cout << table_title;

    for (int i = 0; i < right_padding; i++) {
        std::cout << " ";
    }

    std::cout << "||\n";

    // Single dash horizontal line
    std::cout << "  ";
    for (int i = 0; i < table_width + 4; i++) {
        std::cout << "-";
    }
    std::cout << "\n";

    for (int i = 0; i < states.size() - 1; i += 2) {

        // Left column
        std::cout << "  ||";
        int left_room_length = states[i].get_room_number().size();
        int left_col_left_padding = (col_width - left_room_length) / 2;
        int left_col_right_padding = (col_width - (left_col_left_padding + left_room_length));

        for (int j = 0; j < left_col_left_padding; j++) {
            std::cout << " ";
        }

        std::cout << states[i].get_room_number();

        for (int j = 0; j < left_col_right_padding; j++) {
            std::cout << " ";
        }

        std::cout << "|";

        // Right column
        int right_room_length = states[i + 1].get_room_number().size();
        int right_col_left_padding = (col_width - right_room_length) / 2;
        int right_col_right_padding = (col_width - (right_col_left_padding + right_room_length));

        for (int j = 0; j < right_col_left_padding; j++) {
            std::cout << " ";
        }

        std::cout << states[i + 1].get_room_number();

        for (int j = 0; j < right_col_right_padding; j++) {
            std::cout << " ";
        }
        std::cout << "||\n";
    }

    // Last element in odd number of states
    if (states.size() % 2 == 1) {
        std::cout << "  ||";
        int left_room_length = states[states.size() - 1].get_room_number().size();
        int left_col_left_padding = (col_width - left_room_length) / 2;
        int left_col_right_padding = (col_width - (left_col_left_padding + left_room_length));

        for (int i = 0; i < left_col_left_padding; i++) {
            std::cout << " ";
        }

        std::cout << states[states.size() - 1].get_room_number();

        for (int i = 0; i < left_col_right_padding; i++) {
            std::cout << " ";
        }

        // Empty Column
        std::cout << "|";
        for (int i = 0; i < col_width; i++) {
            std::cout << " ";
        }
        std::cout << "||\n";
    }

    // Double dash horizontal line
    std::cout << "  ";
    for (int i = 0; i < table_width + 4; i++) {
        std::cout << "=";
    }
    std::cout << "\n";

    std::cout << "  Note: Type 'list' at anytime to bring up the room table shown above\n";
    std::cout << "\n==========================================================\n";
}

// Use the trained Q table to find the optimal route from the home state to the state specified
// in the parameters. Print the steps it takes to reach the goal.
void Q_Learn::find_route(int goal) {
    std::cout << "----------------------------------------------------------\n\n";
    std::cout << "  Route from " << states[0].get_room_number() << " to " << states[goal].get_room_number() << ":\n ";
    int cur_state = goal;
    std::vector<int> route;

    // Create a queue holding the states of the optimal route to the home state from the goal
    route.push_back(cur_state);
    while (cur_state != 0) {
        cur_state = max_index(cur_state);
        route.push_back(cur_state);
    }

    // Print directions from the home state to the goal state
    for (int i = route.size() - 1; i >= 0; i--) {
        std::cout << states[route[i]].get_room_number() << " -> ";
    }

    // Print the directions from the goal state back to home state
    for (int i = 1; i < route.size() - 1; i++) {
        std::cout << states[route[i]].get_room_number() << " -> ";
    }
    std::cout << states[route[route.size() - 1]].get_room_number() << "\n";
    std::cout << "\n----------------------------------------------------------\n";
}

// Trains the q matrix through trial and error (q learning) until the matrix converges.
void Q_Learn::train(bool show) {
    std::cout << "\n----------------------------------------------------------\n\n";
    std::cout << "  Training Q Matrix...\n";

    int iteration = 0;
    // Iterate until converged
    while (!converged) {
        iteration++;
        converged = true;

        // Episode loop; Each time this loop runs it is a new episode
        for (int i = 0; i < states.size(); i++) {
            int cur_state = i;

            //Q learn algorithm until the goal state is reached
            while (cur_state != 0) {

                // Choose random next action
                int next_state = random_state(cur_state);
                int max = max_index(next_state);

                int old_q = q_matrix[next_state][cur_state];

                // Update q matrix value
                q_matrix[next_state][cur_state] = r_matrix[next_state][cur_state] + (int)(settings::gamma * q_matrix[max][next_state]);
                int new_q = q_matrix[next_state][cur_state];

                // If any values in the q matrix change, the matrix has not converged
                if (new_q != old_q) {
                    converged = false;

                    // If program is run with "-t" flag, updates to the q matrix will be printed
                    if (show) {
                        std::cout << "  Iteration: " << iteration << " Episode: " << i << "\n";
                        std::cout << "      Action: " << states[cur_state].get_room_number() << " -> " << states[next_state].get_room_number() << "\n";
                        std::cout << "      Q-Val: " << old_q << " -> " << new_q <<"\n\n";
                    }
                }
                cur_state = next_state;
            }
        }
        // Store q matrix values to file after each iteration
        store_matrix(iteration, 1);
    }
    std::cout << "  Training Complete\n";
    std::cout << "\n==========================================================\n";
}

// Returns the index of a random state reachable from the state in the parameters
int Q_Learn::random_state(int cur_state) {
    srand(time(NULL));
    int state = rand() % states.size();

    // Pick new states until the state is reachable from the current state
    while (r_matrix[state][cur_state] == -1) {
        state = rand() % states.size();
    }
    return state;
}

// Returns the index corresponding to the destination state of the highest reward action
// attainable from the state specified in the parameters
int Q_Learn::max_index(int state) {
    int index = 0;
    int max_value = q_matrix[index][state];

    for (int i = 1; i < q_matrix.size(); i++) {

        // Update max value/ index
        if (q_matrix[i][state] > max_value) {
            index = i;
            max_value = q_matrix[i][state];
        }
    }
    return index;
}

// Loads the states from the file specified in settings::adj_list_file
// This file should be an adjacency list, indicating the ties between states.
// The first line in this file is always assumed to represent the goal state
void Q_Learn::load_states() {
    std::cout << "\n==========================================================\n\n";
    std::cout << "  Loading states from '" << settings::adj_list_file << "'\n";

    // Open adjacency list file
    std::ifstream state_stream;
    state_stream.open(settings::adj_list_file.c_str(), std::ios::in);
    if (!state_stream.is_open()) {
        std::cerr << "  Error: Unable to open " << settings::adj_list_file << "\n";
        std::cerr << "  System Exiting...\n";
        exit(1);
    }

    std::string buffer;
    int index = 0;

    // Read file line by line
    while (std::getline(state_stream, buffer)) {
        std::size_t start = 0;
        std::size_t end = buffer.find_first_of(',');

        // Parse out the source state from this line
        std::string source = buffer.substr(start, end);

        // Parse out all states reachable from the source state and add them to a set
        std::set< std::string > targets;
        while (end != std::string::npos) {
            std::string target;
            start = end + 1;
            end = buffer.find_first_of(',', start);
            target = buffer.substr(start, end - start);
            targets.insert(target);
        }

        // Create a room object for the source state and add it to vector of all states
        Room r(source, targets);
        states.push_back(r);

        // Add room number and it's index to map of room numbers
        room_numbers[source] = index++;
    }

    // Print some data on what was parsed
    std::cout << "  " << states.size() << " States Found\n";
    std::cout << "  Goal State: " << states[0].get_room_number() << "\n";
    std::cout << "  Gamma: " << settings::gamma << "\n";
}

// Initialize Q and R matrices to their initial values
// Note: Due to the way rooms and their ties are parsed from the adj list file,
// the Q and R matrices have the form X[to_index][from_index] instead of the usual
// X[from_index][to_index]
void Q_Learn::initialize_matrices() {
    std::cout << "\n----------------------------------------------------------\n\n";
    std::cout << "  Initializing R & Q Matrices...\n";

    int n = states.size();
    r_matrix.resize(n);
    q_matrix.resize(n);

    std::set< std::string > adj_states;
    adj_states = states[0].get_adj_rooms();

    // Initialize Q and R for goal state
    for (int i = 0; i < n; i++) {
        if (adj_states.find(states[i].get_room_number()) != adj_states.end()) {
            r_matrix[0].push_back(100);
        } else {
            r_matrix[0].push_back(-1);
        }
        q_matrix[0].push_back(0);
    }

    // Initialize Q and R for all other states
    for (int i = 1; i < n; i++) {
        adj_states = states[i].get_adj_rooms();
        for (int j = 0; j < n; j++) {
            if (adj_states.find(states[j].get_room_number()) != adj_states.end()) {
                r_matrix[i].push_back(0);
            } else {
                r_matrix[i].push_back(-1);
            }
            q_matrix[i].push_back(0);
        }
    }
    std::cout << "  Storing Initial R & Q Matrices in '" << settings::out_dir << "'\n";
    store_matrix(0, 0);
    store_matrix(0, 1);
}

// Stores the values of the specified matrix in an output file
void Q_Learn::store_matrix(int iteration, int m) {
    std::vector< std::vector<int> > matrix;
    std::string out_file = settings::out_dir;

    // Specifies whether the matrix is Q or R
    switch(m) {
        case 0 :
            out_file.append("r");
            matrix = r_matrix;
            break;

        case 1 :
            out_file.append("q");
            matrix = q_matrix;
            break;

        default :
            std::cerr << "  Error\n";
            std::cerr << "  System exiting...\n";
            exit(1);
    }

    out_file.append("-vals_" + std::to_string(iteration) + ".out");

    std::ofstream stream(out_file, std::ios::trunc);

    // Output values to file
	if (stream.is_open()) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                stream << matrix[i][j] << "  ";
            }
            stream << "\n\n";
        }
        stream.close();
	} else {
		std::cerr << "    Error: Unable to open '" << out_file << "'\n";
		std::cerr << "    System exiting...\n";
		exit(1);
	}
}
