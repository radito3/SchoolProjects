package org.elsys.postfix.operations;

import java.util.EmptyStackException;

import org.elsys.postfix.Calculator;

public class TernaryOperation extends AbstractOperation implements Operation {

	public TernaryOperation(Calculator calculator) {
		super(calculator, "*-\\*");
	}

	@Override
	public void calculate() {
		if (getCalculator().stackSize() < 3) throw new EmptyStackException();
		Double val1 = getCalculator().popValue();
		Double val2 = getCalculator().popValue();
		Double val3 = getCalculator().popValue();
		getCalculator().addValue(-(val1 * val2 * val3));
	}

}
