/*
/ Program: qBot
/ File: settings.h
/ Author: Andrew Holman
/ Assignment: Final
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: December 12, 2017
/
/ Description: Header file for settings namespace
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace settings {
    extern double gamma;

    extern std::string adj_list_file;
    extern std::string coord_file;
    extern std::string out_dir;
}

#endif
