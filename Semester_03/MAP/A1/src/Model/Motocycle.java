package Model;

public class Motocycle implements Vehicle{
    private String colour;
    private String id;

    public Motocycle(String colour, String id) {
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
        return "Motorcycle with ID: " + this.id + " and colour: " + this.colour;
    }
}
