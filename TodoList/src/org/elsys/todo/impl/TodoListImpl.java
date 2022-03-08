package org.elsys.todo.impl;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import org.elsys.todo.*;

public class TodoListImpl implements TodoList {

	private List<Task> tasks = new ArrayList<>();

	public TodoListImpl(String input) {
		String[] lines = input.split("\n");
		for (String line : lines) {
			String[] components = line.split(" \\| ");
			if (components.length != 4) {
				throw new IllegalArgumentException("Invalid input");
			}

			Status status = Status.valueOf(components[0].trim());
			String description = components[1].trim();
			Priority priority = Priority.valueOf(components[2].trim().toUpperCase());
			String[] tags = components[3].split(", ");

			this.tasks.add(new TaskImpl(status, description, priority, tags));
		}
	}
	
	private TodoListImpl(Collection<Task> list) {
		this.tasks = new ArrayList<>(list);
	}

	@Override
	public Boolean isCompleted() {
		return tasks.stream()
				.allMatch(t -> t.getStatus() == Status.DONE);
	}

	@Override
	public Double percentageCompleted() {
		long numCompleted = tasks.stream()
				.filter(t -> t.getStatus() == Status.DONE)
				.count();
		return (double) Math.round((numCompleted / tasks.size()) * 100.0);
	}

	@Override
	public List<Task> getTasks() {
		return tasks;
	}

	@Override
	public TodoList filter(Criteria criteria) {
		return new TodoListImpl(this.getTasks().stream()
				.filter(((AbstractCriteria) criteria)::test)
				.collect(Collectors.toList()));
	}
	
	@Override
	public TodoList join(TodoList other) {
		Set<Task> allTasks = new HashSet<>(tasks);
		allTasks.addAll(other.getTasks());
		return new TodoListImpl(allTasks);
	}

}
