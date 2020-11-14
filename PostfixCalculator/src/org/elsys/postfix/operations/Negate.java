package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Negate extends UnaryOperation {

	public Negate(Calculator calculator) {
		super(calculator, "neg");
	}

	@Override
	public double eval(double val) {
		return -val;
	}

}
