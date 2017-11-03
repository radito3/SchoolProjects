package org.elsys.part1;

public class Ball {
	
	private double volume;
	private Color colour;
	
	public Ball(double volume, Color color) {
		this.volume = volume;
		this.colour = color;
	}

	public Ball(double volume) {
		this(volume, Color.WHITE);
	}

	public double getVolume() {
		return volume;
	}

	public Color getColor() {
		return colour;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((colour == null) ? 0 : colour.hashCode());
		long temp;
		temp = Double.doubleToLongBits(volume);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Ball other = (Ball) obj;
		if (colour != other.colour)
			return false;
		if (Double.doubleToLongBits(volume) != Double.doubleToLongBits(other.volume))
			return false;
		return true;
	}
	
}