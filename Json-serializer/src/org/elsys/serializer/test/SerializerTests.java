package org.elsys.serializer.test;

import org.junit.Test;
import static org.junit.Assert.*;

import org.elsys.serializer.main.Student;

public class SerializerTests extends AbstractSerializerTest {

	@Test
	public void testBasicFunctionAndMapBy() {
		assertEquals(serializer.serialize(student),
			"{ \"first_name\" : \"Pesho\", \"father_name\""
			+ " : \"Ivanov\", \"last_name\" : \"Peshev\", \"grades\" : [ \"2\", \"5\", \"6\" ]"
			+ ", \"friend\" : \"null\" }");
	}
	
	@Test
	public void testPretty() {
		serializer.setPretty(true);
		assertEquals(serializer.serialize(student),
				"{\n"
				+ "   \"first_name\" : \"Pesho\",\n"
				+ "   \"father_name\" : \"Ivanov\",\n"
				+ "   \"last_name\" : \"Peshev\",\n"
				+ "   \"grades\" : [\n"
				+ "      \"2\",\n"
				+ "      \"5\",\n"
				+ "      \"6\"\n"
				+ "   ],\n"
				+ "   \"friend\" : \"null\"\n"
				+ "}");
	}
	
	@Test
	public void testNullFields() {
		student.setFatherName(null);
		serializer.setPretty(false);
		assertEquals(serializer.serialize(student),
				"{ \"first_name\" : \"Pesho\", \"father_name\""
				+ " : \"null\", \"last_name\" : \"Peshev\", \"grades\" : [ \"2\", \"5\", \"6\" ]"
				+ ", \"friend\" : \"null\" }");
		serializer.includeNullFields(false);
		assertEquals(serializer.serialize(student),
				"{ \"first_name\" : \"Pesho\", \"last_name\" : \"Peshev\", \"grades\" : [ \"2\", \"5\", \"6\" ] }");
	}
	
	@Test
	public void testRecursion() {
		student.setFriend(new Student("1", "2", "3"));
		serializer.setPretty(false);
		student.setFatherName(null);
		serializer.includeNullFields(true);
		assertEquals(serializer.serialize(student), "{ \"first_name\" : \"Pesho\", \"father_name\""
				+ " : \"null\", \"last_name\" : \"Peshev\", \"grades\" : [ \"2\", \"5\", \"6\" ],"
				+ " \"{ \"first_name\" : \"1\", \"father_name\" : \"2\", \"last_name\" : \"3\","
				+ " \"grades\" : \"null\", \"friend\" : \"null\" }\" }");
	}
	
}
