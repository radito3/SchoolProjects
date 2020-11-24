package org.elsys.todo.impl;

import java.util.Arrays;
import java.util.Objects;

import org.elsys.todo.*;

public class TaskImpl implements Task {

	private Status status;
	private String description;
	private Priority priority;
	private String[] tags;
	
	public TaskImpl(Status status, String description, Priority priority, String[] tags) {
		this.status = status;
		this.description = description;
		this.priority = priority;
		this.tags = tags;
	}

	@Override
	public Status getStatus() {
		return status;
	}

	@Override
	public String getDescription() {
		return description;
	}

	@Override
	public Priority getPriority() {
		return priority;
	}

	@Override
	public String[] getTags() {
		return tags;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o)
			return true;
		if (o == null || getClass() != o.getClass())
			return false;
		TaskImpl task = (TaskImpl) o;
		return status == task.status
			&& Objects.equals(description, task.description)
			&& priority == task.priority
			&& Arrays.equals(tags, task.tags);
	}

	@Override
	public int hashCode() {
		int result = Objects.hash(status, description, priority);
		result = 31 * result + Arrays.hashCode(tags);
		return result;
	}

	@Override
	public String toString() {
		return "TaskImpl{" + "status=" + status + ", description='" + description + '\'' + ", priority=" + priority + ", tags="
			+ Arrays.toString(tags) + '}';
	}
}
