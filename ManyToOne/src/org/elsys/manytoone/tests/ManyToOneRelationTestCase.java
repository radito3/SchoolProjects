package org.elsys.manytoone.tests;

import static org.junit.Assert.*;

import java.util.Collection;

import org.elsys.manytoone.ManyToOneRelation;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class ManyToOneRelationTestCase {

	private static ManyToOneRelation<String, Integer> map;
	
	@Before
	public void setUp() throws Exception {
		map = new ManyToOneRelation<>();
	}

	@After
	public void tearDown() throws Exception {
		map = null;
	}

	@Test
	public void testConnect() {
		assertTrue(map.connect("One", new Integer(1)));
	}

	@Test
	public void testContainsSource() {
		map.connect("One", new Integer(1));
		assertTrue(map.containsSource("One"));
	}

	@Test
	public void testContainsTarget() {
		map.connect("One", new Integer(1));
		assertTrue(map.containsTarget(new Integer(1)));
	}

	@Test
	public void testGetTarget() {
		map.connect("One", new Integer(1));
		assertEquals(map.getTarget("One"), new Integer(1));
	}

	@Test
	public void testGetSources() {
		Integer one = new Integer(1);
		map.connect("One", one);
		map.connect("One1", one);
		Collection<String> keys = map.getSources(one);
		assertEquals(keys.size(), 2);
	}

	@Test
	public void testDisconnectSource() {
		map.connect("One", new Integer(1));
		assertTrue(map.containsSource("One"));
		map.disconnectSource("One");
		assertFalse(map.containsSource("One"));
	}

	@Test
	public void testDisconnect() {
		Integer one = new Integer(1);
		map.connect("One", one);
		assertTrue(map.containsTarget(one));
		map.disconnect(one);
		assertFalse(map.containsTarget(one));
	}

	@Test
	public void testGetTargets() {
		map.connect("One", new Integer(1));
		map.connect("Two", new Integer(2));
		Collection<Integer> values = map.getTargets();
		assertEquals(values.size(), 2);
	}

}
