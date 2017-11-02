package org.elsys.netprog.rest;

import java.util.HashMap;

import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;

@Path("/KeyValueDB")
public class KeyValueDB {
	//accessed with ...:8081/KeyValueDB/rest/KeyValueDB

	private static HashMap<String, String> db = new HashMap<String, String>();
	
	static {
		db.put("item1", "value1");
		db.put("item2", "value2");
		db.put("item3", "value3");
	}
	
	@GET
	@Produces(MediaType.TEXT_PLAIN)
	public String getData() {
		StringBuilder sb = new StringBuilder();
		db.keySet().stream().forEach(key -> sb.append(String.format("%s: %s\n", key, db.get(key))));
		return sb.toString();
	}
	
	@PUT
	public void setData(@QueryParam("key") String key, @QueryParam("value") String value) {
		db.put(key, value);
	}
	
	@DELETE
	public void removeData(@QueryParam("key") String key) {
		db.remove(key);
	}
}
