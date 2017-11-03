package org.elsys.netprog.sockets;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class EchoServer {

	public static void main(String[] args) throws IOException {
		ServerSocket serverSocket = null;
		try {
			serverSocket = new ServerSocket(10001);
			Socket clientSocket = serverSocket.accept();
			System.out.println("client connected from " + clientSocket.getInetAddress());
			PrintWriter out = 
					new PrintWriter(clientSocket.getOutputStream(), true);
			BufferedReader in = new BufferedReader(
					new InputStreamReader(clientSocket.getInputStream()));
			
			String inputLine;
			
			while ((inputLine = in.readLine()) != null) {
				out.println(inputLine);
				System.out.println(calc(inputLine));
				
				if (inputLine.equals("exit")) {
					break;
				}
			}
		} catch (Throwable t) {
			System.out.println(t.getMessage());
		} finally {
			if (serverSocket != null && !serverSocket.isClosed()) {
				serverSocket.close();
			}
		}
	}
	
	private static Integer calc(String input) throws Exception {
		Pattern inputPattern = Pattern.compile("^\\s*(\\d+)\\s*([\\+\\-\\*/])\\s*(\\d+)\\s*$");
		Matcher matcher = inputPattern.matcher(input);
		
		if (!matcher.matches()) {
			throw new Exception("Kofti vhod");
		}
		
		int l = Integer.parseInt(matcher.group(1));
		int r = Integer.parseInt(matcher.group(3));
		
		switch (matcher.group(2)) {
		case "+":
			return l + r;
		case "-":
			return l - r;
		case "*":
			return l * r;
		case "/":
			return l / r;
		default:
			throw new Exception("Invalid operation");
		}
	}

}
