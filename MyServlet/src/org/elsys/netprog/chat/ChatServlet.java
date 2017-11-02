package org.elsys.netprog.chat;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/Chat")
public class ChatServlet extends HttpServlet {
	// tested and working on http://localhost:8081/MyServlet/Chat
	
	private static final long serialVersionUID = 1L;
    private static ArrayList<Message> messages = new ArrayList<Message>();
    
    static {
    	messages.add(new Message("Ivan", "Zdrasti"));
    	messages.add(new Message("Miro", "Dai pari za pasti"));
    }

    public ChatServlet() {
        super();
    }

    private String generatePage() {
    	StringBuilder html = new StringBuilder();
    	html.append("<!DOCTYPE html><html><body><div>");
    	messages.stream().forEach(el -> html.append(String.format("<p>%s</p>", el.getMessage())));
		html.append("<form method='POST'>"+
				"<label>Name: </label><input type='text' name='name' placeholder='Name' />" +
				"<label>Message: </label><input type='text' name='message' placeholder='Message' /> " +
				"<input type='submit' />" +
				"</form>" +
				"<a href=\"/MyServlet/Chat\"><button>Refresh</button></a>" +
				"</div></body></html>");
		return html.toString();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		request.setCharacterEncoding("UTF-8");
		response.getOutputStream().println(generatePage());
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		request.setCharacterEncoding("UTF-8");
		
		String name = request.getParameter("name");
		String message = request.getParameter("message");
		
		if (name != "" && message != "") {
			messages.add(new Message(name, message));
		}
		response.getOutputStream().println(generatePage());
	}

}
