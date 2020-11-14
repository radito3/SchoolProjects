package org.elsys.postfix.operations;

import java.util.EmptyStackException;

import org.elsys.postfix.Calculator;

public abstract class UnaryOperation extends AbstractOperation {

	public UnaryOperation(Calculator calculator, String token) {
		super(calculator, token);
	}

	@Override
	public void calculate() {
		if (getCalculator().stackSize() < 1) throw new EmptyStackException();
		Double value = getCalculator().popValue();
		double result = eval(value);
		getCalculator().addValue(result);
	}
	
	public abstract double eval(double val);

}
