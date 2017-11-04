package org.elsys.todo;

import static org.junit.Assert.*;

import org.elsys.todo.Criteria;
import org.elsys.todo.Priority;
import org.elsys.todo.Status;
import org.elsys.todo.TodoList;
import org.junit.Test;

public class TodoListImplTest {

	private TodoList todoList = TodoList.parse(
			"TODO    | Do OOP homework              | Low    | school, programming\r\n" + 
			"TODO    | Get 8 hours of sleep.        | Low    | health\r\n" + 
			"DOING   | Party hard.                  | Normal | social\r\n" + 
			"DONE    | Netflix and chill.           | Normal | tv shows\r\n" + 
			"TODO    | Find missing socks.          | Low    | meh\r\n" + 
			"");
	
	private TodoList completedTodoList = TodoList.parse(
			"DONE    | Do OOP homework              | Low    | school, programming\r\n" + 
			"DONE    | Get 8 hours of sleep.        | Low    | health\r\n" + 
			"DONE    | Party hard.                  | Normal | social\r\n" + 
			"DONE    | Netflix and chill.           | Normal | tv shows\r\n" + 
			"DONE    | Find missing socks.          | Low    | meh\r\n" + 
			"");
	
	private TodoList todoList1 = TodoList.parse(
			"TODO    | Do OOP homework              | Normal | school, programming\r\n" + 
			"TODO    | Get 8 hours of sleep.        | High   | health\r\n" + 
			"DOING   | Stuff.                       | Low    | school\r\n" + 
			"DONE    | Netflix and chill.           | Low    | tv shows\r\n" + 
			"TODO    | Find missing socks.          | Normal | meh\r\n" + 
			"");
	
	private TodoList todoList2 = TodoList.parse(
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" + 
			"DONE    | Get 8 hours of sleep.        | High   | health\r\n" + 
			"DONE    | Stuff.                       | Low    | school\r\n" + 
			"DONE    | Netflix and chill.           | Low    | tv shows\r\n" + 
			"DONE    | Find missing socks.          | Normal | meh\r\n" + 
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"");

	private TodoList todoList3 = TodoList.parse(
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" + 
			"TODO    | Get 8 hours of sleep.        | High   | health\r\n" + 
			"TODO    | Stuff.                       | Low    | school\r\n" + 
			"TODO    | Netflix and chill.           | Low    | tv shows\r\n" + 
			"DONE    | Find missing socks.          | Normal | meh\r\n" + 
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"DONE    | Do OOP homework              | Normal | school, programming\r\n" +
			"");
	
	@Test
	public void testIsCompleted() {
		assertEquals(false, todoList.isCompleted());
		assertEquals(true, completedTodoList.isCompleted());
	}

	@Test
	public void testGetTasks() {
		assertEquals(5, todoList.getTasks().size());
	}
	
	@Test
	public void filterByStatus() {
		TodoList filtered = todoList.filter(Criteria.status(Status.DOING));
		assertEquals(1, filtered.getTasks().size());
	}
	
	@Test
	public void filterByPriority() {
		TodoList filtered = todoList.filter(Criteria.priority(Priority.HIGH));
		TodoList filteredNew = todoList.filter(Criteria.priority(Priority.NORMAL));
		assertEquals(0, filtered.getTasks().size());
		assertEquals(2, filteredNew.getTasks().size());
	}
	
	@Test
	public void filterByNotCriteria() {
		assertEquals(5, todoList
				.filter(Criteria.priority(Priority.HIGH).not())
				.getTasks().size());
		assertEquals(3, todoList
				.filter(Criteria.priority(Priority.NORMAL).not())
				.getTasks().size());
	}	
	
	@Test
	public void filterByAnd() {
		assertEquals(2, todoList1.filter(Criteria.priority(Priority.NORMAL)
				.and(Criteria.status(Status.TODO))).getTasks().size());
	}
	
	@Test
	public void filterByTags() {
		assertEquals(2, todoList1.filter(Criteria
				.tags(new String[] { "school" })).getTasks().size());
	}
	
	@Test
	public void filterByOr() {
		assertEquals(5, todoList1.filter(Criteria.status(Status.TODO)
				.or(Criteria.priority(Priority.LOW))).getTasks().size());
	}

	@Test
	public void percentageTest() {
		assertEquals(new Double(100.00), todoList2.percentageCompleted());
		assertEquals(new Double(70.00), todoList3.percentageCompleted());
	}
	
}
