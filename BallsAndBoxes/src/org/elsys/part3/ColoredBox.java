package org.elsys.part3;

import org.elsys.part1.Ball;
import org.elsys.part1.Box;
import org.elsys.part1.Color;

public class ColoredBox extends Box {

	private final Color colour;
	
	public ColoredBox(Color color, double capacity) {
		super(capacity);
		this.colour = color;
	}

	public Color getColor() {
		return colour;
	}
	
	public boolean add(Ball b) {
		return !(b == null || b.getColor() != colour) && super.add(b);
	}
	
}
