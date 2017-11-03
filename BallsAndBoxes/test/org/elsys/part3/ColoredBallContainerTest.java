package org.elsys.part3;

import static org.junit.Assert.*;

import org.elsys.part1.Ball;
import org.elsys.part1.Color;
import org.elsys.part3.ColoredBallContainer;
import org.junit.Test;

public class ColoredBallContainerTest {

	@Test
	public void testAdd() {
		ColoredBallContainer container = new ColoredBallContainer(Color.BLUE);
		Ball ball1 = new Ball(10.1, Color.BLUE);
		Ball ball2 = new Ball(10.2, Color.BLUE);
		Ball ball3 = new Ball(16, Color.BLACK);

		assertTrue(container.add(ball1));
		assertTrue(container.add(ball2));
		assertFalse(container.add(ball3));
	}

	@Test
	public void testRemove() {
		ColoredBallContainer container = new ColoredBallContainer(Color.BLUE);
		Ball ball1 = new Ball(10.1, Color.BLUE);

		container.add(ball1);
		assertTrue(container.remove(ball1));
		assertFalse(container.contains(ball1));
	}

	@Test
	public void testCapacity() {
		ColoredBallContainer container = new ColoredBallContainer(Color.BLUE);

		container.add(new Ball(2.01, Color.BLUE));
		container.add(new Ball(2.0, Color.BLUE));
		container.add(new Ball(16,Color.BLACK));
		assertEquals(4.01,
				container.getVolume(), 0.01);
	}
	
	@Test
	public void testClear() {
		ColoredBallContainer container = new ColoredBallContainer(Color.BLUE);
		container.add(new Ball(2.01, Color.BLUE));
		container.add(new Ball(2.0, Color.BLUE));
		assertFalse(container.size() == 0);
		container.clear(); 
		assertTrue(container.size() == 0);
	}
	
	@Test
	public void testColor() {
		ColoredBallContainer container = new ColoredBallContainer(Color.BLUE);
		container.add(new Ball(2.01, Color.BLUE));
		assertTrue(container.size() == 1);
		container.add(new Ball(2.01, Color.BLACK));
		assertTrue(container.size() == 1);
	}
}
