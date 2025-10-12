package View;

import Controller.Service;
import Exceptions.MyException;
import Model.Expression.ArithmeticExpression;
import Model.Expression.RefExpression;
import Model.Expression.RelationalExpression;
import Model.Expression.VariableExpression;
import Model.ProgState;
import Model.Statement.*;
import Model.Type.*;
import Model.Value.BoolValue;
import Model.Value.IntValue;
import Model.Value.StringValue;
import Model.Value.Value;
import Repository.IRepository;
import Repository.Repository;
import Utils.*;
import Model.Expression.ValueExpression;
import View.Command.ExitCommand;
import View.Command.RunExample;

import java.io.BufferedReader;

public class View {
    public static IStatement example1(){
        //int v; v = 2; Print(v)
        IStatement ex1= new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                new PrintStatement(new VariableExpression("v"))));
        return ex1;
    }

    public static IStatement example2(){
        // int a; int b; a=2+3*5; b=a+1; Print(b)
        IStatement ex2 = new CompStatement(
                new VarDeclStatement("a", new IntType()),
                new CompStatement(new VarDeclStatement("b", new IntType()),
                new CompStatement(
                        new AssignStatement("a", new ArithmeticExpression("+", new ValueExpression(new IntValue(2)), new ArithmeticExpression("*", new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                        new CompStatement(
                                new AssignStatement("b", new ArithmeticExpression("+", new VariableExpression("a"), new ValueExpression(new IntValue(1)))),
                                new PrintStatement(new VariableExpression("b"))))));
        return ex2;
    }

    public static IStatement example3(){
        // bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)
        IStatement ex3 = new CompStatement(
                new VarDeclStatement("a", new BoolType()),
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompStatement(
                                        new IfStatement(new VariableExpression("a"), new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                                new AssignStatement("v", new ValueExpression(new IntValue(3)))),
                                        new PrintStatement(new VariableExpression("v")))
                                )
                        )
                );
        return ex3;
    }
    public static IStatement example4(){
        // string varf; varf = "test.in"; openRFile(varf); int varc; readFile(varf, varc); Print(varc); readFile(varf, varc); Print(varc); closeRFile(varf);
        IStatement ex4 = new CompStatement(
                new VarDeclStatement("varf", new StringType()),
                new CompStatement(
                        new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompStatement(
                                new OpenRFile(new VariableExpression("varf")),
                                new CompStatement(
                                        new VarDeclStatement("varc", new IntType()),
                                        new CompStatement(
                                                new ReadFile(new VariableExpression("varf"), "varc"),
                                                new CompStatement(
                                                        new PrintStatement(new VariableExpression("varc")),
                                                        new CompStatement(
                                                                new ReadFile(new VariableExpression("varf"), "varc"),
                                                                new CompStatement(
                                                                        new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseRFile(new VariableExpression("varf"))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        return ex4;
    }

    public static IStatement example5() {
        // Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        IStatement ex5 = new CompStatement(
                new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(
                                new VarDeclStatement("a",
                                        new RefType(new RefType(
                                                new IntType()))),
                                new CompStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompStatement(
                                                new PrintStatement(new VariableExpression(
                                                        "v")),
                                                new PrintStatement(new VariableExpression(
                                                        "a"))
                                                        )
                                                )
                                        )
                )
        );
        return ex5;
}

    private static IStatement example6() {
        // Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        IStatement ex6 =  new CompStatement(
                new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(
                                new VarDeclStatement("a",
                                        new RefType(new RefType(
                                                new IntType()))),
                                new CompStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompStatement(
                                                new PrintStatement(new RefExpression(
                                                        new VariableExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression(
                                                        "+",
                                                        new RefExpression(new RefExpression(
                                                                new VariableExpression("a"))),
                                                        new ValueExpression(
                                                                new IntValue(5))
                                                                )
                                                        )
                                        )
                                )
                        )
                )
        );
        return ex6;
    }

    private static IStatement example7() {
        // Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
        IStatement ex7 = new CompStatement(
                new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(
                                new PrintStatement(new RefExpression(new VariableExpression("v"))),
                                new CompStatement(
                                        new WriteHeapStatement("v",
                                                new ValueExpression(
                                                        new IntValue(30))),
                                        new PrintStatement(new ArithmeticExpression("+",
                                                new RefExpression(new VariableExpression(
                                                        "v")),
                                                new ValueExpression(
                                                        new IntValue(5))))))));
        return ex7;
    }

    private static IStatement example8() {
        // Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        IStatement ex8 =  new CompStatement(
                new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(
                                new VarDeclStatement("a",
                                        new RefType(new RefType(
                                                new IntType()))),
                                new CompStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompStatement(
                                                new NewStatement("v", new ValueExpression(
                                                        new IntValue(30))),
                                                new PrintStatement(new RefExpression(
                                                        new RefExpression(new VariableExpression(
                                                                "a")))))))));
        return ex8;
        }

    private static IStatement example9() {
        // int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        IStatement ex9 = new CompStatement(
                new VarDeclStatement("v", new IntType()),
                new CompStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(4))),
                        new CompStatement(
                                new WhileStatement(
                                        new RelationalExpression(">", 
                                                new VariableExpression("v"),
                                                new ValueExpression(
                                                        new IntValue(0))
                                                ),
                                        new CompStatement(
                                                new PrintStatement(new VariableExpression(
                                                        "v")),
                                                new AssignStatement("v",
                                                        new ArithmeticExpression("-",
                                                                new VariableExpression("v"),
                                                                new ValueExpression(
                                                                        new IntValue(1)))))),
                                new PrintStatement(new VariableExpression("v")))));
        return ex9;
    }
    private static IStatement example10() {
        // int v; Ref int a; v=10; new(a,22); fork(wH(a,30);v=32;print(v);print(rH(a))); print(v);print(rH(a))
        IStatement ex10 = new CompStatement(
                new VarDeclStatement("v", new IntType()),
                new CompStatement(
                        new VarDeclStatement("a", new RefType(new IntType())),
                        new CompStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(10))),
                                new CompStatement(
                                        new NewStatement("a", new ValueExpression(new IntValue(22))),
                                        new CompStatement(
                                                new ForkStatement(
                                                        new CompStatement(
                                                                new WriteHeapStatement("a",
                                                                        new ValueExpression(new IntValue(30))),
                                                                new CompStatement(
                                                                        new AssignStatement("v",
                                                                                new ValueExpression(new IntValue(32))),
                                                                                new PrintStatement(new VariableExpression("v"))))),
                                                new CompStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new RefExpression(new VariableExpression("a")))))))));
        return ex10;
    }

    private static IStatement example11(){
        // Ref (int) a; int v; new(a, 10); fork(v=20;fork(wH(a, 40); print(rH(a));); print(v);); v = 30; print(v); print(rH(a));
        IStatement ex11 = new CompStatement(
                new VarDeclStatement("a", new RefType(new IntType())),
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new NewStatement("a", new ValueExpression(new IntValue(10))),
                                new CompStatement(
                                        new ForkStatement(
                                                new CompStatement(
                                                        new AssignStatement("v", new ValueExpression(new IntValue(20))),
                                                        new CompStatement(
                                                                new ForkStatement(
                                                                        new CompStatement(
                                                                                new WriteHeapStatement("a", new ValueExpression(new IntValue(40))),
                                                                                new CompStatement(
                                                                                        new PrintStatement(new RefExpression(new VariableExpression("a"))),
                                                                                        new PrintStatement(new VariableExpression("v"))
                                                                                )
                                                                        )
                                                                ),
                                                                new PrintStatement(new VariableExpression("v"))
                                                        )
                                                )),
                                                new CompStatement(
                                                        new AssignStatement("v", new ValueExpression(new IntValue(30))),
                                                        new CompStatement(
                                                                new PrintStatement(new VariableExpression("v")),
                                                                new PrintStatement(new RefExpression(new VariableExpression("a")))
                                                        )
                                                )
                                        )
                                )
                        )
                );
        return ex11;
    }

    private static ProgState createState (IStatement program){
        MyIDictionary<String, Type> typeEnv = new MyDictionary<>();
        program.typecheck(typeEnv);
        MyIStack<IStatement> stack = new MyStack<>();
        MyIDictionary<String, Value> symTable = new MyDictionary<>();
        MyIList<Value> output = new MyList<>();
        MyIDictionary<StringValue, BufferedReader> fileTable = new MyDictionary<>();
        MyIHeap<Integer, Value> heap = new MyHeap<>();
        return new ProgState(stack, symTable, output, program, fileTable, heap);
    }

    private static Service createService(IStatement program, String logFilePath){
        ProgState state = createState(program);
        IRepository repo = new Repository(state, logFilePath);
        return new Service(repo);
    }

    public static void main(String[] args) {
        TextMenu menu = new TextMenu();

        menu.addCommand(new RunExample("1", example1(), createService(example1(), "log1.txt")));
        menu.addCommand(new RunExample("2", example2(), createService(example2(), "log2.txt")));
        menu.addCommand(new RunExample("3", example3(), createService(example3(), "log3.txt")));
        menu.addCommand(new RunExample("4", example4(), createService(example4(), "log4.txt")));
        menu.addCommand(new RunExample("5", example5(), createService(example5(), "log5.txt")));
        menu.addCommand(new RunExample("6", example6(), createService(example6(), "log6.txt")));
        menu.addCommand(new RunExample("7", example7(), createService(example7(), "log7.txt")));
        menu.addCommand(new RunExample("8", example8(), createService(example8(), "log8.txt")));
        menu.addCommand(new RunExample("9", example9(), createService(example9(), "log9.txt")));
        menu.addCommand(new RunExample("10", example10(), createService(example10(), "log10.txt")));
        menu.addCommand(new RunExample("11", example11(), createService(example11(), "log11.txt")));
        menu.addCommand(new ExitCommand("0", "Exit"));

        try {
            menu.show();
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }
}