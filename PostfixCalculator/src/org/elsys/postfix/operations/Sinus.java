package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Sinus  extends UnaryOperation {

	public Sinus(Calculator calculator) {
		super(calculator, "sin");
	}

	@Override
	public double eval(double val) {
		return Math.sin(val);
	}

}
