package org.elsys.manytoone.tests;

import static org.junit.Assert.*;

import org.elsys.manytoone.ManyToOneRelation;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class ManyToOneRelationTestCase {

	private static ManyToOneRelation<String, Integer> map;
	
	@Before
	public void setUp() throws Exception {
		map = new ManyToOneRelation<>();
		assertNotNull(map);
	}

	@After
	public void tearDown() throws Exception {
		// what is this supposed to do?
	}

	@Test
	public void testConnect() {
		
	}

	@Test
	public void testContainsSource() {
		
	}

	@Test
	public void testContainsTarget() {
		
	}

	@Test
	public void testGetTarget() {
		
	}

	@Test
	public void testGetSources() {
		
	}

	@Test
	public void testDisconnectSource() {
		
	}

	@Test
	public void testDisconnect() {
		
	}

	@Test
	public void testGetTargets() {
		
	}

}
