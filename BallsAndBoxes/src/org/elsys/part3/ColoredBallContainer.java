package org.elsys.part3;

import org.elsys.part1.Ball;
import org.elsys.part1.BallContainer;
import org.elsys.part1.Color;

public class ColoredBallContainer extends BallContainer {

	private final Color colour;
	
	public ColoredBallContainer(Color color) {
		super();
		this.colour = color;
	}

	public Color getColor() {
		return colour;
	}
	
	public boolean add(Ball b) {
		return !(b == null || b.getColor() != colour) && super.add(b);
	}
}
