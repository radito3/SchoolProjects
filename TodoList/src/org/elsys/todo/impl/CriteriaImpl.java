package org.elsys.todo.impl;

import java.util.function.Predicate;

import org.elsys.todo.*;

public class CriteriaImpl implements Criteria {

	private Predicate<Task> filter;
	
	public CriteriaImpl(Status status) {
		this.filter = t -> t.getStatus() == status;
	}
	
	public CriteriaImpl(Priority priority) {
		this.filter = t -> t.getPriority() == priority;
	}
	
	public CriteriaImpl(String[] tags) {
		this.filter = t -> {
				for (String filterStr : t.getTags()) {
					for (String resStr : tags) {
						if (filterStr.equals(resStr)) {
							return true;
						}
					}
				}
				return false;
			};
	}
	
	public CriteriaImpl(Predicate<Task> other) {
		this.filter = other;
	}
	
	@Override
	public Criteria and(Criteria other) {		
		return new CriteriaImpl(filter.and(other.getFilter()));
	}

	@Override
	public Criteria or(Criteria other) {
		return new CriteriaImpl(filter.or(other.getFilter()));
	}

	@Override
	public Criteria not() {
		return new CriteriaImpl(filter.negate());
	}

	@Override
	public Predicate<Task> getFilter() {
		return filter;
	}

}
