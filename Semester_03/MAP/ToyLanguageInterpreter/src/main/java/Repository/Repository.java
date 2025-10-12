package Repository;

import Exceptions.MyException;
import Model.ProgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Repository implements IRepository {
    private List<ProgState> repository;
    private String filePath;

    public Repository(ProgState state){
        this.repository = new ArrayList<>();
        this.repository.add(state);
    }

    public Repository(ProgState state, String filePath){
        this.repository = new ArrayList<>();
        this.repository.add(state);
        this.filePath = filePath;
    }

    public void setFilePath() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the file path: ");
        this.filePath = scanner.nextLine();
        scanner.close();
    }

    @Override
    public void add(ProgState s) {
        this.repository.add(s);
    }

    @Override
    public void logProgState(ProgState state) throws MyException {
        if (this.filePath == null)
            setFilePath();
        PrintWriter logFile;
        try {
            logFile = new PrintWriter(new BufferedWriter(new FileWriter(filePath, true)));
        } catch (IOException e) {
            throw new MyException("Error opening log file");
        }
        logFile.println(state.toString());
        logFile.close();
    }
    @Override
    public List<ProgState> getProgList() {
        return repository;
    }

    @Override
    public void setProgList(List<ProgState> progList) {
        this.repository = progList;
    }
}
