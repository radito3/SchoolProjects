package org.elsys.postfix;

import org.junit.Test;

public class Rot3Test extends CalculatorAbstractTest {

	@Test
	public void test() {
		input("20");
		input("10");
		input("5");
		input("rot3");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(20);
	}
}
