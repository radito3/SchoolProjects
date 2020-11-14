package org.elsys.postfix.operations;

import org.elsys.postfix.Calculator;

public class Division extends BinaryOperation {
	
	public Division(Calculator calculator) {
		super(calculator, "/");
	}

	@Override
	public double eval(double val1, double val2) {
		return val2 / val1;
	}

}
