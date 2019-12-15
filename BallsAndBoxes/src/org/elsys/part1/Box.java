package org.elsys.part1;

import java.util.Comparator;
import java.util.Iterator;

public class Box extends BallContainer {

	protected final double capacity;
	
	public Box(double capacity) {
		super();
		this.capacity = capacity;
	}

	public Iterator<Ball> getBallsFromSmallest() {
		container.sort(Comparator.comparingDouble(Ball::getVolume));
		return container.iterator();
	}
	
	public boolean add(Ball b) {
		return b == null || this.getVolume() + b.getVolume() > capacity 
				? false : super.add(b);
	}
}
