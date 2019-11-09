package org.elsys.todo.impl;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

import org.elsys.todo.*;

public class TodoListImpl implements TodoList {

	private List<Task> tasks = new ArrayList<>();

	public TodoListImpl(String input) {
		String[] lines = input.split("\n");
		for (String line : lines) {
			Pattern pattern = Pattern.compile("^(\\w+)\\s+\\|\\s(.+)\\s+\\|\\s(\\w+)\\s*\\|\\s(.+)\r$");
			Matcher matcher = pattern.matcher(line);
			if (!matcher.matches()) 
				continue;

			Status status = Status.valueOf(Status.class, matcher.group(1));
			String descr = matcher.group(2);
			Priority priority = Priority.valueOf(Priority.class, matcher.group(3).toUpperCase());
			String[] tags = matcher.group(4).split(", ");

			this.tasks.add(new TaskImpl(status, descr, priority, tags));
		}
	}
	
	public TodoListImpl(List<Task> list) {
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
		return new Double(Math.round((numCompleted / tasks.size()) * 100.0));
	}

	@Override
	public List<Task> getTasks() {
		return tasks;
	}

	@Override
	public TodoList filter(Criteria criteria) {
		return new TodoListImpl(this.getTasks().stream()
				.filter(criteria.getFilter())
				.collect(Collectors.toList()));
	}
	
	@Override
	public TodoList join(TodoList other) {
		Set<Task> allTasks = new HashSet<>(tasks);
		allTasks.addAll(other.getTasks());
		return new TodoListImpl(new ArrayList<>(allTasks));
	}

}
