package View.gui;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.SimpleObjectProperty;
import Model.ProgState;
import Model.Value.Value;
import Model.Statement.IStatement;
import Controller.Service;
import Exceptions.StackException;
import Utils.MyIHeap;
import Utils.MyIStack;
import Utils.MyDictionary;
import Utils.MyList;
import Utils.MyStack;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.io.BufferedReader;
import Model.Value.StringValue;
import java.lang.reflect.Field;
import javafx.util.Pair;
import Utils.ISemaphoreTable;

public class MainWindowController {
    private Service controller;
    private ProgState selectedProgram;

    @FXML
    private TextField numberOfPrgStatesTextField;

    @FXML
    private TableView<Map.Entry<Integer, Value>> heapTableView;
    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> heapAddressColumn;
    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> heapValueColumn;

    @FXML
    private ListView<String> outputListView;
    @FXML
    private ListView<String> fileTableListView;
    @FXML
    private ListView<Integer> prgStateIdentifiersListView;
    @FXML
    private ListView<String> exeStackListView;

    @FXML
    private TableView<Map.Entry<String, Value>> symTableView;
    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symTableVarNameColumn;
    @FXML
    private TableColumn<Map.Entry<String, Value>, String> symTableValueColumn;

    @FXML
    private Button runOneStepButton;

    @FXML
    private TableView<Map.Entry<Integer, Pair<Integer, List<Integer>>>> semaphoreTableView;
    @FXML
    private TableColumn<Map.Entry<Integer, Pair<Integer, List<Integer>>>, Integer> semaphoreIndexColumn;
    @FXML
    private TableColumn<Map.Entry<Integer, Pair<Integer, List<Integer>>>, Integer> semaphoreValueColumn;
    @FXML
    private TableColumn<Map.Entry<Integer, Pair<Integer, List<Integer>>>, String> semaphoreListColumn;

    public void setController(Service controller) {
        this.controller = controller;
        populateAll();
    }

    @FXML
    public void initialize() {
        heapAddressColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getKey().toString()));
        heapValueColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getValue().toString()));

        symTableVarNameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getKey()));
        symTableValueColumn
                .setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getValue().toString()));

        prgStateIdentifiersListView.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> {
                    if (newValue != null) {
                        selectedProgram = controller.getRepository().getProgList().stream()
                                .filter(p -> p.getId() == newValue)
                                .findFirst()
                                .orElse(null);
                        populateExeStack();
                        populateSymTable();
                        symTableView.refresh();
                    }
                });

        initializeSemaphoreTableView();
    }

    private void initializeSemaphoreTableView() {
        semaphoreIndexColumn.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getKey()));
        semaphoreValueColumn.setCellValueFactory(p -> new SimpleObjectProperty<>(p.getValue().getValue().getKey()));
        semaphoreListColumn.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getValue().getValue().toString()));
    }

    private void populateAll() {
        populateHeapTable();
        populateOutput();
        populateFileTable();
        populatePrgStateIdentifiers();
        populateNumberOfPrgStates();
        populateSemaphoreTable();

        if (selectedProgram == null && !controller.getRepository().getProgList().isEmpty()) {
            selectedProgram = controller.getRepository().getProgList().get(0);
            prgStateIdentifiersListView.getSelectionModel().select(0);
        }

        if (selectedProgram != null) {
            populateExeStack();
            populateSymTable();
        }
    }

    private void populateNumberOfPrgStates() {
        numberOfPrgStatesTextField.setText(String.valueOf(controller.getRepository().getProgList().size()));
    }

    private void populateHeapTable() {
        MyIHeap<Integer, Value> heap = controller.getRepository().getProgList().get(0).getHeap();
        ObservableList<Map.Entry<Integer, Value>> heapEntries = FXCollections.observableArrayList(
                heap.getHeap().entrySet());
        heapTableView.setItems(heapEntries);
    }

    private void populateOutput() {
        ObservableList<String> output = FXCollections.observableArrayList();
        if (!controller.getRepository().getProgList().isEmpty()) {
            MyList<Value> outList = (MyList<Value>) controller.getRepository().getProgList().get(0).getOutput();
            output.addAll(outList.getList().stream()
                        .map(Object::toString)
                        .collect(Collectors.toList()));
        }
        outputListView.setItems(output);
    }

    private void populateFileTable() {
        ObservableList<String> files = FXCollections.observableArrayList();
        if (!controller.getRepository().getProgList().isEmpty()) {
            MyDictionary<StringValue, BufferedReader> fileTable = (MyDictionary<StringValue, BufferedReader>) controller.getRepository()
                    .getProgList().get(0).getFileTable();
            files.addAll(fileTable.getValues().stream()
                    .filter(br -> br != null)
                    .map(br -> br.toString())
                    .collect(Collectors.toList()));
        }
        fileTableListView.setItems(files);
    }

    private void populatePrgStateIdentifiers() {
        ObservableList<Integer> identifiers = FXCollections.observableArrayList();
        identifiers.addAll(controller.getRepository().getProgList().stream()
                .map(ProgState::getId)
                .collect(Collectors.toList()));
        prgStateIdentifiersListView.setItems(identifiers);
    }

    private void populateExeStack() {
        ObservableList<String> exeStack = FXCollections.observableArrayList();
        if (selectedProgram != null) {
            List<String> stackElements = new ArrayList<>();
            MyIStack<IStatement> stack = selectedProgram.getExecStack();
            MyIStack<IStatement> tempStack = new MyStack<>();
            try {
                while (!stack.isEmpty()) {
                    IStatement stmt = stack.pop();
                    stackElements.add(0, stmt.toString());
                    tempStack.push(stmt);
                }
                while (!tempStack.isEmpty()) {
                    stack.push(tempStack.pop());
                }
            } catch (StackException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setHeaderText(null);
                alert.setContentText("Error accessing stack: " + e.getMessage());
                alert.showAndWait();
            }

            exeStack.addAll(stackElements);
        }
        exeStackListView.setItems(exeStack);
    }

    private void populateSymTable() {
        ObservableList<Map.Entry<String, Value>> symTableEntries = FXCollections.observableArrayList();
        if (selectedProgram != null) {
            MyDictionary<String, Value> symTable = (MyDictionary<String, Value>) selectedProgram.getSymbolTable();
            symTableEntries.addAll(symTable.getDict().entrySet());
        }
        symTableView.setItems(symTableEntries);
        symTableView.refresh();
    }

    private void populateSemaphoreTable() {
        if (!controller.getRepository().getProgList().isEmpty()) {
            ISemaphoreTable semTable = controller.getRepository().getProgList().get(0).getSemaphoreTable();
            ObservableList<Map.Entry<Integer, Pair<Integer, List<Integer>>>> semaphoreList = 
                FXCollections.observableArrayList(semTable.getContent().entrySet());
            semaphoreTableView.setItems(semaphoreList);
            semaphoreTableView.refresh();
        }
    }

    @FXML
    private void runOneStep() {
        if (controller == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("No program selected!");
            alert.showAndWait();
            return;
        }

        List<ProgState> prgList = controller.removeCompletedPrg(controller.getRepository().getProgList());
        if (prgList.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Nothing left to execute!");
            alert.showAndWait();
            return;
        }

        try {
            controller.oneStepForAllProg(prgList);
            populateAll();
        } catch (InterruptedException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }
}