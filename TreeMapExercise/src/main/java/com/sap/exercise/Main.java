package com.sap.exercise;

public class Main {

	private static boolean isPalindrome(String s) {
    		int n = s.length();
       		if (n < 2) {
            		return true;
        	}
        	for (int i = 0; i < (n / 2); ++i) {
            		if (s.charAt(i) != s.charAt(n - i - 1)) {
                		return false;
            		}
        	}
        	return true;
    	}

	public static void main(String[] args) {
		//TODO write here
	}

}

