package Repository;

import Exceptions.ParkingLotException;
import Model.Vehicle;

public class Repo implements IRepository{
    private Vehicle[] vehicles;
    private int current_index;

    public Repo(int size){
        this.vehicles = new Vehicle[size];
        this.current_index = 0;
    }

    @Override
    public void add(Vehicle vehicle) throws ParkingLotException {
        if(this.current_index > this.vehicles.length){
            throw new ParkingLotException("The parking lot is full!");
        }
        this.vehicles[this.current_index] = vehicle;
        this.current_index++;
    }

    @Override
    public void remove(Vehicle vehicle) throws ParkingLotException {
        if(this.current_index == 0){
            throw new ParkingLotException("The parking lot is empty!");
        }
        for(int i = 0; i < this.current_index; i++){
            if(this.vehicles[i].equals(vehicle)){
                for(int j = i; j < this.current_index - 1; j++){
                    this.vehicles[j] = this.vehicles[j + 1];
                }
                this.current_index--;
                break;
            }
        }
    }

    @Override
    public void display_all_red_vehicles(){
        for(int i = 0; i < this.current_index; i++){
            if(this.vehicles[i].getColour().equals("red")){
                System.out.println(this.vehicles[i].toString());
            }
        }
    }
}
