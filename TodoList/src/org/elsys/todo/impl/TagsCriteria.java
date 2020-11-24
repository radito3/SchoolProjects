package org.elsys.todo.impl;

import org.elsys.todo.Task;

import java.util.Set;

public class TagsCriteria extends AbstractCriteria {

    private String[] tags;

    public TagsCriteria(String[] tags) {
        this.tags = tags;
    }

    @Override
    public boolean test(Task task) {
        Set<String> taskTags = Set.of(task.getTags());
        for (String tag : tags) {
            if (taskTags.contains(tag)) {
                return true;
            }
        }
        return false;
    }
}
