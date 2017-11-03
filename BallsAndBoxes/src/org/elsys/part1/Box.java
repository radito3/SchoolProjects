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
		container.sort(new Comparator<Ball>() {
			@Override
			public int compare(Ball b1, Ball b2) {
				return b1.getVolume() == b2.getVolume() ? 
						0 : b1.getVolume() < b2.getVolume() ? -1 : 1;
			}
		});
		return container.iterator();
	}
	
	public boolean add(Ball b) {
		return b == null || this.getVolume() + b.getVolume() > capacity 
				? false : super.add(b);
	}
}