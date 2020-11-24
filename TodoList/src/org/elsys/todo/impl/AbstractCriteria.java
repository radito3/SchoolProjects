package org.elsys.todo.impl;

import org.elsys.todo.Criteria;
import org.elsys.todo.Task;

public abstract class AbstractCriteria implements Criteria {

    public abstract boolean test(Task task);

    @Override
    public Criteria and(Criteria other) {
        return new AbstractCriteria() {
            @Override
            public boolean test(Task task) {
                return AbstractCriteria.this.test(task) && ((AbstractCriteria) other).test(task);
            }
        };
    }

    @Override
    public Criteria or(Criteria other) {
        return new AbstractCriteria() {
            @Override
            public boolean test(Task task) {
                return AbstractCriteria.this.test(task) || ((AbstractCriteria) other).test(task);
            }
        };
    }

    @Override
    public Criteria not() {
        return new AbstractCriteria() {
            @Override
            public boolean test(Task task) {
                return !AbstractCriteria.this.test(task);
            }
        };
    }
}
