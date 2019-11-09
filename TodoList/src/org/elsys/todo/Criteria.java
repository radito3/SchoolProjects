package org.elsys.todo;

import java.util.function.Predicate;

import org.elsys.todo.impl.CriteriaImpl;

public interface Criteria {

	static Criteria status(Status status) {
		return new CriteriaImpl(status);
	}

	static Criteria priority(Priority priority) {
		return new CriteriaImpl(priority);
	}

	static Criteria tags(String[] tags) {
		return new CriteriaImpl(tags);
	}

	Predicate<Task> getFilter();
	
	/**
	 * Creates new Criteria instance representing conjunction with the provided
	 * as argument Criteria.
	 * 
	 * @param other
	 * @return the new Criteria instance
	 */
	Criteria and(Criteria other);

	/**
	 * Creates new Criteria instance representing disjunction with the provided
	 * as argument Criteria.
	 * 
	 * @param other
	 * @return the new Criteria instance
	 */
	Criteria or(Criteria other);

	/**
	 * Creates new Criteria instance representing negation of the Criteria.
	 * 
	 * @param other
	 * @return the new Criteria instance
	 */
	Criteria not();

}
