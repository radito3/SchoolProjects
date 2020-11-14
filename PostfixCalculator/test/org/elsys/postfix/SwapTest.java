package org.elsys.postfix;

import org.junit.Test;

public class SwapTest extends CalculatorAbstractTest {

	@Test
	public void test() {
		input("20");
		input("10");
		input("swap");
		inputCtrlC();
		runCalculator();
		assertCalculatorLastValue(20);
	}
}
