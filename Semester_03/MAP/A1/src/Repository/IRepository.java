package Repository;
import Model.Vehicle;

public interface IRepository {
    void add(Vehicle vehicle);
    void remove(Vehicle vehicle);
    void display_all_red_vehicles();
}
