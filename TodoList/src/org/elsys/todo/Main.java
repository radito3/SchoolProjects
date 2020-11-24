package org.elsys.todo;

public class Main {

    private static TodoList todoList = TodoList.parse(
        "TODO    | Do OOP homework              | Low    | school, programming\r\n" +
            "TODO    | Get 8 hours of sleep.        | Low    | health\r\n" +
            "DOING   | Party hard.                  | Normal | social\r\n" +
            "DONE    | Netflix and chill.           | Normal | tv shows\r\n" +
            "TODO    | Find missing socks.          | Low    | meh\r\n" +
            "");

    private static TodoList completedTodoList = TodoList.parse(
        "DONE    | Do OOP homework              | Low    | school, programming\r\n" +
            "DONE    | Get 8 hours of sleep.        | Low    | health\r\n" +
            "DONE    | Party hard.                  | Normal | social\r\n" +
            "DONE    | Netflix and chill.           | Normal | tv shows\r\n" +
            "DONE    | Find missing socks.          | Low    | meh\r\n" +
            "");

    private static TodoList todoList1 = TodoList.parse(
        "TODO    | Do OOP homework              | Normal | school, programming\r\n" +
            "TODO    | Get 8 hours of sleep.        | High   | health\r\n" +
            "DOING   | Stuff.                       | Low    | school\r\n" +
            "DONE    | Netflix and chill.           | Low    | tv shows\r\n" +
            "TODO    | Find missing socks.          | Normal | meh\r\n" +
            "");

    private static TodoList todoList2 = TodoList.parse(
        "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Get 8 hours of sleep.        | High   | health\r\n" +
            "DONE    | Stuff.                       | Low    | school\r\n" +
            "DONE    | Netflix and chill.           | Low    | tv shows\r\n" +
            "DONE    | Find missing socks.          | Normal | meh\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "");

    private static TodoList todoList3 = TodoList.parse(
        "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "TODO    | Get 8 hours of sleep.        | High   | health\r\n" +
            "TODO    | Stuff.                       | Low    | school\r\n" +
            "TODO    | Netflix and chill.           | Low    | tv shows\r\n" +
            "DONE    | Find missing socks.          | Normal | meh\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "DONE    | Do OOP homework              | Normal | school, programming\r\n" +
            "");

    public static void main(String[] args) {
        System.out.println(todoList.getTasks());
        System.out.println(todoList2.getTasks());
        System.out.println(todoList3.getTasks());
        System.out.println(todoList1.getTasks());

        System.out.println(todoList.isCompleted());
        System.out.println(completedTodoList.isCompleted());

        TodoList filtered = todoList.filter(Criteria.status(Status.DOING));
        System.out.println(filtered.getTasks());

        TodoList filtered1 = todoList.filter(Criteria.priority(Priority.HIGH));
        TodoList filteredNew = todoList.filter(Criteria.priority(Priority.NORMAL));
        System.out.println(filtered1.getTasks());
        System.out.println(filteredNew.getTasks());

        System.out.println(todoList
                               .filter(Criteria.priority(Priority.HIGH).not())
                               .getTasks());
        System.out.println(todoList
                               .filter(Criteria.priority(Priority.NORMAL).not())
                               .getTasks());

        System.out.println(todoList1.filter(Criteria.tags(new String[] { "school" })).getTasks());
    }

}