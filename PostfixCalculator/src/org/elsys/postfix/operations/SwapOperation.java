package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class SwapOperation extends BinaryOperation {

	public SwapOperation(Calculator calculator) {
		super(calculator, "swap");
	}

	@Override
	public double eval(double val1, double val2) {
		getCalculator().addValue(val1);
		return val2;
	}

}
