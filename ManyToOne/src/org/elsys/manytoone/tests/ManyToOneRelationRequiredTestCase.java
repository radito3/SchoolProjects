package org.elsys.manytoone.tests;

import org.elsys.manytoone.ManyToOneRelation;
import org.junit.Test;

import static org.junit.Assert.*;

public class ManyToOneRelationRequiredTestCase {

	@Test
	public void testEqualsTrue() throws Exception {
		ManyToOneRelation<String, Integer> relation1 = new ManyToOneRelation<String, Integer>();
		ManyToOneRelation<String, Integer> relation2 = new ManyToOneRelation<String, Integer>();
		relation1.connect("Integer1", new Integer(1));
		relation1.connect("Integer2", new Integer(2));
		relation2.connect("Integer1", new Integer(1));
		relation2.connect("Integer2", new Integer(2));
		assertEquals(relation1, relation2);
	}

	@Test
	public void testEqualsFalse() throws Exception {
		ManyToOneRelation<String, Integer> relation1 = new ManyToOneRelation<String, Integer>();
		ManyToOneRelation<String, Integer> relation2 = new ManyToOneRelation<String, Integer>();
		relation1.connect("Integer1", new Integer(1));
		relation2.connect("Integer1", new Integer(1));
		relation2.connect("Integer2", new Integer(2));
		assertNotEquals(relation1, relation2);
	}
}
