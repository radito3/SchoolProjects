package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Plus extends BinaryOperation {
	
	public Plus(Calculator calculator) {
		super(calculator, "+");
	}

	@Override
	public double eval(double val1, double val2) {
		return val2 + val1;
	}

}
