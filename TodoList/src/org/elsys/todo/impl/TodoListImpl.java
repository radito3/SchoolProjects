package org.elsys.todo.impl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

import org.elsys.todo.*;

public class TodoListImpl implements TodoList {

	private List<Task> tasks = new ArrayList<Task>();

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
		this.tasks = new ArrayList<Task>(list);
	}

	@Override
	public Boolean isCompleted() {
		return tasks.stream()
				.allMatch(t -> t.getStatus() == Status.DONE);
	}

	@Override
	public Double percentageCompleted() {
		double numCompleted = tasks.stream()
				.filter(t -> t.getStatus() == Status.DONE)
				.collect(Collectors.toList()).size();
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
		return new TodoListImpl(Stream.concat(this.getTasks().stream(), other.getTasks().stream())
					.distinct().collect(Collectors.toList()));
	}

}
