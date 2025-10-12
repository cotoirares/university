package View;
import Controller.Controller;
import Repository.Repo;
import Model.Car;
import Model.Bike;
import Model.Motocycle;
import Exceptions.ParkingLotException;

public class Main {
    public static void main(String[] args) {
        try {
            Repo repo = new Repo(100);
            Controller controller = new Controller(repo);
            controller.addVehicle(new Car("red", "c1"));
            controller.addVehicle(new Bike("blue", "b1"));
            controller.addVehicle(new Motocycle("blue", "m1"));
            controller.addVehicle(new Motocycle("red", "m2"));
            controller.addVehicle(new Motocycle("red", "m3"));
            controller.addVehicle(new Motocycle("green", "m4"));
            controller.displayAllRedVehicles();
        }
        catch (ParkingLotException e) {
            System.out.println(e.getMessage());
        }
    }
}
