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
		List<String> lines = Arrays.asList(input.split("\n"));
		lines.stream()
			.forEach(line -> {
				Pattern pattern = 
						Pattern.compile("^(\\w+)\\s+\\|\\s(.+)\\s+\\|\\s(\\w+)\\s*\\|\\s(.+)\r$");
				Matcher matcher = pattern.matcher(line);
				if (matcher.matches()) {
					Status status = Status.valueOf(Status.class, matcher.group(1));
					String descr = matcher.group(2);
					Priority priority = Priority.valueOf(Priority.class, matcher.group(3).toUpperCase());
					String[] tags = matcher.group(4).split(", ");
					this.tasks.add(new TaskImpl(status, descr, priority, tags));
				}
			});
	}
	
	public TodoListImpl(List<Task> list) {
		this.tasks = list;
	}

	@Override
	public Boolean isCompleted() {
		return tasks.stream()
				.filter(t -> t.getStatus() != Status.DONE)
				.count() == 0;
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
		return new TodoListImpl(other.getTasks().stream()
				.filter(t -> !this.getTasks().contains(t))
				.peek(t -> this.getTasks().add(t))
				.collect(Collectors.toList()));
	}

}
