package org.elsys.postfix;

import java.util.EmptyStackException;

import org.junit.Test;

public class TernaryOperationTest extends CalculatorAbstractTest  {

	@Test(expected = EmptyStackException.class)
	public void testWithNotEnoughValuesInStack() {
		input("11");
		input("*-\\*");
		inputCtrlC();
		runCalculator();
	}

	
	@Test
	public void test() {
		input("10");
		input("5");
		input("6");
		input("*-\\*");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(-300);
	}
}
