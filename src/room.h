/*
/ Program: qBot
/ File: room.h
/ Author: Andrew Holman
/ Assignment: Final
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: December 12, 2017
/
/ Description: Header file for room class
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <set>

class Room {
	public:
		Room(std::string r, std::set< std::string > s);
        std::string get_room_number();
        std::set< std::string > get_adj_rooms();

	private:
		std::string room_number; // Room number of this room
        std::set< std::string > adj_rooms; // Set of room numbers of adjacent rooms
};

#endif
