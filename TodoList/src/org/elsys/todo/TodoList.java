package org.elsys.todo;

import java.util.List;

import org.elsys.todo.impl.TodoListImpl;

public interface TodoList {

	static TodoList parse(String input) {
		return new TodoListImpl(input);
	}

	Boolean isCompleted();

	Double percentageCompleted();

	List<Task> getTasks();

	TodoList filter(Criteria criteria);

	TodoList join(TodoList other);
}
