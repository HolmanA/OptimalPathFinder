/*
/ Program: qBot
/ File: room.cpp
/ Author: Andrew Holman
/ Last Date Modified: December 12, 2017
/
/ Description: cpp file for Room class. A room object represents a single room from the CF building 4th floor
*/

#include "room.h"

// Constructor for Room object
Room::Room(std::string r, std::set< std::string > s) {
    room_number = r;
    adj_rooms = s;
}

// Getter method for retrieving this room's number
std::string Room::get_room_number() {
    return room_number;
}

// Getter method for retrieving the room numbers of rooms adjacent to this room
std::set< std::string > Room::get_adj_rooms() {
    return adj_rooms;
}
