package org.elsys.serializer;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.lang.reflect.Field;

public class JsonSerializer extends AbstractSerializer implements Serializer {

	@Override
	public String serialize(Object obj) {
		String serialized = "{ ";
		List<Field> fields = getFieldsToSerialize(obj.getClass());
		if (!isDirectlySerializable(obj)) {
			try {
				for (Field f : fields) {
					f.setAccessible(true);
					if (f.isAnnotationPresent(Ignore.class)) {
						continue;
					}
					String fieldName = f.isAnnotationPresent(MapBy.class) ? 
							f.getAnnotation(MapBy.class).value() : f.getName();
					if (f.get(obj) == null) {
						serialized += nullFields ? "\"" + fieldName + "\" : \"null\", " : "";
						continue;
					}
					if (isArray(f.get(obj)) || isCollection(f.get(obj))) {
						serialized += "\"" + fieldName + "\" : " + serializeCollection(
								isArray(f.get(obj)) ? Arrays.asList(f.get(obj)) : 
									(Collection<?>) f.get(obj)) + ", ";
						continue;
					}
					if (!isDirectlySerializable(f.get(obj))) {
						serialized += "\"" + serialize(f.get(obj)) + "\", ";
						continue;
					}
					serialized += "\"" + fieldName + "\" : \"" + f.get(obj) + "\", ";
				}
			} catch (IllegalArgumentException | IllegalAccessException e) {
				e.printStackTrace();
			}
			if (pretty) {
				serialized = serialized.replace("{ ", "{\n   ").replaceAll(", ", ",\n   ");
				serialized = serialized.substring(0, serialized.length() - 5) + "\n}";
			} else {
				serialized = serialized.substring(0, serialized.length() - 2) + " }";
			}
		} else {
			serialized = "\"" + obj.toString() + "\"";
		}
		return serialized;
	}

	private String serializeCollection(Collection<?> collection) {
		String srlz = "[ ";
		for (Object o : collection) {
			srlz += serialize(o) + ", ";
		}
		if (pretty) {
			srlz = srlz.replace("[ ", "[\n      ").replaceAll("\"\\.", "      \"").replaceAll("\", ", "\",\n      ");
			srlz = srlz.substring(0, srlz.length() - 8) + "\n   ]";
		} else {
			srlz = srlz.substring(0, srlz.length() - 2) + " ]";
		}
		return srlz;
	}

}
