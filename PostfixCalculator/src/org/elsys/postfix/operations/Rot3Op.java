package org.elsys.postfix.operations;

import java.util.EmptyStackException;

import org.elsys.postfix.Calculator;

public class Rot3Op extends AbstractOperation implements Operation {

	public Rot3Op(Calculator calculator) {
		super(calculator, "rot3");
	}

	@Override
	public void calculate() {
		if (getCalculator().stackSize() < 3) throw new EmptyStackException();
		Double val1 = getCalculator().popValue();
		Double val2 = getCalculator().popValue();
		Double val3 = getCalculator().popValue();
		getCalculator().addValue(val2);
		getCalculator().addValue(val1);
		getCalculator().addValue(val3);
	}

}
