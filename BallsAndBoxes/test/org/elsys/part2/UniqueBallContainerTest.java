package org.elsys.part2;

import static org.junit.Assert.*;

import org.elsys.part1.Ball;
import org.elsys.part1.Color;
import org.elsys.part2.UniqueBallContainer;
import org.junit.Test;

public class UniqueBallContainerTest {

	@Test
	public void testAdd() {
		UniqueBallContainer container = new UniqueBallContainer();
		Ball ball1 = new Ball(10.1);
		Ball ball2 = new Ball(10.2, Color.BLACK);
		Ball ball3 = new Ball(10.2, Color.BLACK);
		
		assertEquals(ball2, ball3);
		assertTrue(container.add(ball1));
		assertTrue(container.add(ball2));
		assertFalse(container.add(ball3));
	}

	@Test
	public void testRemove() {
		UniqueBallContainer container = new UniqueBallContainer();
		Ball ball1 = new Ball(10.1);

		container.add(ball1);
		assertTrue(container.remove(ball1));
		assertFalse(container.contains(ball1));
	}

	@Test
	public void testCapacity() {
		UniqueBallContainer container = new UniqueBallContainer();

		container.add(new Ball(2.01, Color.BLACK));
		container.add(new Ball(2.0));
		container.add(new Ball(2.01, Color.BLACK));
		assertEquals(4.01,
				container.getVolume(), 0.01);
	}
	
	@Test
	public void testClear() {
		UniqueBallContainer container = new UniqueBallContainer();
		container.add(new Ball(2.01));
		container.add(new Ball(2.0));
		assertFalse(container.size() == 0);
		container.clear(); 
		assertTrue(container.size() == 0);
	}

}
