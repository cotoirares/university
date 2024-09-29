//
// Created by Rares-Andrei Cotoi on 23.04.2024.
//

#include "ui.h"
#include "Service.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void UI::start() {
    // Create the service
    Service service = Service();
    int useroption;
    while(true){
        print_menu();
        cout << "Enter option: ";
        cin >> useroption;
        if(useroption == 0) {
            break;
        }
        else if (useroption == 1){
            std::string bodyStyle, typeOfEngine;
            int autonomy;
            cout << "Enter body style: ";
            cin >> bodyStyle;
            cout << "Enter type of engine: ";
            cin >> typeOfEngine;
            if (typeOfEngine == "Electric"){
                cout << "Enter autonomy: ";
                cin >> autonomy;
                service.addCar(bodyStyle, typeOfEngine, autonomy);
            }
            else{
                service.addCar(bodyStyle, typeOfEngine, 0);
            }
        }
        else if (useroption == 2){
            vector<Car*> cars = service.getCars();
            for (Car* car : cars){
                cout << car->toString() << endl;
            }
        }
        else if (useroption == 3){
            string fileName = "saved_cars.txt";
            double MaxPrice;
            cout<<"Enter max price: ";
            cin>>MaxPrice;
            service.writeToFile(fileName, MaxPrice);
        }
    }
}

void UI::print_menu(){
    cout << "1. Add car" << endl;
    cout << "2. Show all cars with all information" << endl;
    cout << "3. Write to file" << endl;
    cout << "0. Exit" << endl;
}
