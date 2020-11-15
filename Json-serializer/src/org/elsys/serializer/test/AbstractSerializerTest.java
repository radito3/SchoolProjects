package org.elsys.serializer.test;

import java.util.Arrays;

import org.elsys.serializer.JsonSerializer;
import org.elsys.serializer.Serializer;
import org.elsys.serializer.main.Student;
import org.junit.Before;

public abstract class AbstractSerializerTest {

	protected Student student = new Student();
	protected Serializer serializer = new JsonSerializer();
	
	@Before
	public void beforeTest() {
		student.setName("Pesho");
		student.setFatherName("Ivanov");
		student.setLastName("Peshev");
		student.setGrades(Arrays.asList(2, 5, 6));
		student.setFriend(null);
	}
	
}
