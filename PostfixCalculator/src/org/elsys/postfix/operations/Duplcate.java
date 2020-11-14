package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Duplcate extends UnaryOperation {

	public Duplcate(Calculator calculator) {
		super(calculator, "dup");
	}

	@Override
	public double eval(double val) {
		getCalculator().addValue(val);
		return val;
	}

}
