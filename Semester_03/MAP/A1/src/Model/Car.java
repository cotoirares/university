package Model;

public class Car implements Vehicle{
    private String colour;
    private String id;

    public Car(String colour, String id) {
        this.colour = colour;
        this.id = id;
    }

    public String getColour() {
        return colour;
    }

    public void setColour(String colour) {
        this.colour = colour;
    }

    @Override
    public String toString(){
        return "Car with ID: " + this.id + " and colour: " + this.colour;
    }
}
