//
// Created by Rares-Andrei Cotoi on 01.04.2024.
//

#include "ui.h"

void UI::run() {
    int UserInput;
    while (true) {
        user_menu();
        std::cin>>UserInput;
        if (UserInput == 1) {
            std::string name;
            float latitude_to_remove, longitude_to_remove;
            std::cout<<"Enter the name of the school you want to remove: ";
            std::cin>>name;
            std::cout<<"Enter the latitude of the school you want to remove: ";
            std::cin>>latitude_to_remove;
            std::cout<<"Enter the longitude of the school you want to remove: ";
            std::cin>>longitude_to_remove;
            bool removed = service.delete_school(name, latitude_to_remove, longitude_to_remove);
            if (removed)
                std::cout<<"School removed successfully\n";
            else
                std::cout<<"School not found. Please provide a valid input\n";
        }
        else if (UserInput == 2) {
            School* schools = service.get_all_schools_sorted();
            int size = service.get_size();
            for (int i = 0; i < size; i++) {
                std::cout<<"Name: "<<schools[i].getName()<<" Latitude: "<<schools[i].getLatitude()<<" Longitude: "<<schools[i].getLongitude()<<" Date to visit: "<<schools[i].getDateToVisit()<<" Visited: "<<schools[i].checkIfVisited()<<"\n";
            }
        }
        else if (UserInput == 3) {
            std::string date;
            std::cin>>date;
            School* new_schools = service.mark_as_visited_by_date(date);
            /// printing new schools array
            int size = service.get_size();
            for (int i = 0; i < size; i++) {
                std::cout<<"Name: "<<new_schools[i].getName()<<" Latitude: "<<new_schools[i].getLatitude()<<" Longitude: "<<new_schools[i].getLongitude()<<" Date to visit: "<<new_schools[i].getDateToVisit()<<" Visited: "<<new_schools[i].checkIfVisited()<<"\n";
            }
        }
        else {
            break;
        }
    }
}

void UI::user_menu() {
    std::cout<<"1. Remove a school from the list\n";
    std::cout<<"2. Show all the schools sorted by name\n";
    std::cout<<"3. Given a date d, mark all schools having the planned date of visit before d as visited and show only the schools that must be visited after that date\n";
}
