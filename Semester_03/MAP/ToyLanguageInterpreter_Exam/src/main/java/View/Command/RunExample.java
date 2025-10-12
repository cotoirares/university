package View.Command;

import Controller.Service;
import Model.Statement.IStatement;
import Exceptions.MyException;

public class RunExample extends Command{
    private Service service;
    private boolean beenExecuted;

    public RunExample(String key, IStatement statement, Service service) {
        super(key, statement.toString());
        this.service = service;
        this.beenExecuted = false;
    }

    @Override
    public void execute() {
        if (beenExecuted){
            System.out.println("The program has already been executed");
            return;
        }
        try {
            service.allStep();
            beenExecuted = true;
        }
        catch (MyException e){
            System.out.println(e.getMessage());
        }
    }
    public boolean hasBeenExecuted() {
        return beenExecuted;
      }
}
