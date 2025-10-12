package Model;

public class Bike implements Vehicle{
    private String colour;
    private String id;

    public Bike(String colour, String id) {
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
        return "Bike with ID: " + this.id + " and colour: " + this.colour;
    }
}
