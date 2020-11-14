package org.elsys.postfix.operations;

import java.util.ArrayList;
import java.util.List;

import org.elsys.postfix.Calculator;

public class CompositeOperation extends AbstractOperation {

	@SuppressWarnings("unused")
	private List<Operation> operations = new ArrayList<Operation>();
	
	public CompositeOperation(Calculator calculator, String token) {
		super(calculator, token);
	}

	@Override
	public void calculate() {
		
	}
	
	public void addOperation(Operation op) {
		
	}

}
