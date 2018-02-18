/*
/ Program: qBot
/ File: settings.cpp
/ Author: Andrew Holman
/ Assignment: Final
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: December 14, 2017
/
/ Description: cpp file for settings namespace. Used to specify various program settings
*/

#include "settings.h"

namespace settings {
    double gamma = 0.9;
    std::string adj_list_file = "../data/train/room-adjacency-list.csv";
    std::string coord_file = "../data/train/door-coordinates.csv";
    std::string out_dir = "../out/";
}
