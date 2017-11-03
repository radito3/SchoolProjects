package org.elsys.part2;

import static org.junit.Assert.*;

import java.util.Iterator;

import org.elsys.part1.Ball;
import org.elsys.part1.Color;
import org.elsys.part2.UniqueBox;
import org.junit.Test;

public class UniqueBoxTest {

	@Test
	public void testMaxCapacity() {
		UniqueBox UniqueBox = new UniqueBox(10);
		assertTrue(UniqueBox.add(new Ball(5, Color.BLACK)));
		assertFalse(UniqueBox.add(new Ball(5, Color.BLACK)));
		assertFalse(UniqueBox.add(new Ball(6)));
	}

	@Test
	public void testNull() {
		UniqueBox UniqueBox = new UniqueBox(10);
		assertFalse(UniqueBox.add(null));
	}

	@Test
	public void testIterator() {
		UniqueBox UniqueBox = new UniqueBox(10);
		UniqueBox.add(new Ball(3));
		UniqueBox.add(new Ball(2));
		UniqueBox.add(new Ball(1));

		Iterator<Ball> iter = UniqueBox.getBallsFromSmallest();
		assertEquals(1, iter.next().getVolume(), 0.01);
		assertEquals(2, iter.next().getVolume(), 0.01);
		assertEquals(3, iter.next().getVolume(), 0.01);
		assertFalse(iter.hasNext());
	}
}
