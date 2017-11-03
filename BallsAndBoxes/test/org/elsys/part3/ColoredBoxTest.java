package org.elsys.part3;

import static org.junit.Assert.*;

import java.util.Iterator;

import org.elsys.part1.Ball;
import org.elsys.part3.ColoredBox;
import org.elsys.part1.Color;
import org.junit.Test;

public class ColoredBoxTest {

	@Test
	public void testMaxCapacity() {
		ColoredBox ColoredBox = new ColoredBox(Color.BLACK, 10);
		assertTrue(ColoredBox.add(new Ball(5, Color.BLACK)));
		assertFalse(ColoredBox.add(new Ball(6, Color.BLACK)));
		assertFalse(ColoredBox.add(new Ball(5, Color.BLUE)));
	}

	@Test
	public void testNull() {
		ColoredBox ColoredBox = new ColoredBox(Color.BLACK, 10);
		assertFalse(ColoredBox.add(null));
	}

	@Test
	public void testIterator() {
		ColoredBox ColoredBox = new ColoredBox(Color.BLACK, 10);
		ColoredBox.add(new Ball(3, Color.BLACK));
		ColoredBox.add(new Ball(2, Color.BLACK));
		ColoredBox.add(new Ball(1, Color.BLACK));

		Iterator<Ball> iter = ColoredBox.getBallsFromSmallest();
		assertEquals(1, iter.next().getVolume(), 0.01);
		assertEquals(2, iter.next().getVolume(), 0.01);
		assertEquals(3, iter.next().getVolume(), 0.01);
		assertFalse(iter.hasNext());
	}
}
