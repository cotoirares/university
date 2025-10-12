package Controller;
import Model.Vehicle;
import Repository.Repo;

public class Controller {
    private Repo repo;

    public Controller(Repo repo) {
        this.repo = repo;
    }

    public void addVehicle(Vehicle vehicle) {
        this.repo.add(vehicle);
    }

    public void removeVehicle(Vehicle vehicle) {
        this.repo.remove(vehicle);
    }

    public void displayAllRedVehicles() {
        this.repo.display_all_red_vehicles();
    }
}
