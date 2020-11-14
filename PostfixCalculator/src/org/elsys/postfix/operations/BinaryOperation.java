package org.elsys.postfix.operations;

import java.util.EmptyStackException;

import org.elsys.postfix.Calculator;

public abstract class BinaryOperation extends AbstractOperation {

	public BinaryOperation(Calculator calculator, String token) {
		super(calculator, token);
	}

	@Override
	public void calculate() {
		if (getCalculator().stackSize() < 2) throw new EmptyStackException();
		Double val1 = getCalculator().popValue();
		Double val2 = getCalculator().popValue();
		double result = eval(val1, val2);
		getCalculator().addValue(result);
	}
	
	public abstract double eval(double val1, double val2);

}
