package org.elsys.part1;

import java.util.ArrayList;
import java.util.List;

public class BallContainer {
	
	protected List<Ball> container;
	
	public BallContainer() {
		container = new ArrayList<Ball>();
	}

	public boolean add(Ball b) {
		return b == null ? false : container.add(b);
	}

	public boolean remove(Ball b) {
		return container.remove(b);
	}

	public double getVolume() {
		return container.stream().mapToDouble(b -> b.getVolume()).sum();
	}

	public int size() {
		return container.size();
	}

	public void clear() {
		container.clear();
	}

	public boolean contains(Ball b) {
		return container.contains(b);
	}

}