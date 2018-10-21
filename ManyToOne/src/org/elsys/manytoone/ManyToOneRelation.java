package org.elsys.manytoone;

import java.util.*;

/**
 * Introduces the notation of many-to-one relation. This is where the M and O of
 * the type signature comes from.
 *
 * Many unique "source" objects refer to one and only "target" object.
 *
 * The class maintains a connection between the target and all the sources that
 * are referring to it.
 *
 * @author Kiril Mitov k.mitov@sap.com
 *
 * @param <M>
 *            the type of the "source" objects.
 * @param <O>
 *            the type of the "target" objects.
 */
public class ManyToOneRelation<M, O> {
	
	private Map<Set<M>, O> map;

	public ManyToOneRelation() {
		map = new LinkedHashMap<>();
	}
	
	/**
	 * Connects the given source with the given target. If this source was
	 * previously connected with another target the old connection is lost.
	 *
	 * @param source
	 * @param target
	 * @return
	 */
	public boolean connect(M source, O target) {
	    if (!map.containsValue(target)) {
            map.put(new HashSet<>(Collections.singleton(source)), target);
            return true;
        }
        for (Map.Entry<Set<M>, O> entry : map.entrySet()) {
            for (M key : entry.getKey()) {
                if (key.equals(source)) {
                    map.put(new HashSet<>(Collections.singleton(source)), target);
                    return true;
                }
            }
            entry.getKey().add(source);
        }
        return true;
	}

	/**
	 * @param source
	 * @return <code>true</code> if the relation contains the given source
	 */
	public boolean containsSource(M source) {
        for (Map.Entry<Set<M>, O> entry : map.entrySet()) {
            for (M key : entry.getKey()) {
                if (key.equals(source)) {
                    return true;
                }
            }
        }
		return false;
	}

	/**
	 * @param target
	 * @return <code>true</code> if the relation contains the given target
	 */
	public boolean containsTarget(O target) {
		return map.containsValue(target);
	}

	/**
	 * @param source
	 * @return the target with which this source is connected
	 */
	public O getTarget(M source) {
        for (Map.Entry<Set<M>, O> entry : map.entrySet()) {
            for (M key : entry.getKey()) {
                if (key.equals(source)) {
                    return entry.getValue();
                }
            }
        }
		return null;
	}

	/**
	 * @param target
	 * @return all the targets that are connected with this source or empty
	 *         collection if there are no sources connected with this target.
	 */
	public Collection<M> getSources(O target) {
        for (Map.Entry<Set<M>, O> entry : map.entrySet()) {
            if (entry.getValue().equals(target)) {
                return entry.getKey();
            }
        }
        return Collections.emptySet();
	}

	/**
	 * Removes the connection between this source and the corresponding target.
	 * Other sources will still point to the same target.
	 *
	 * The target is removed if this was the only source pointing to it and
	 * {@link #containsTarget(Object)} will return false.
	 *
	 * @param source
	 */
	public void disconnectSource(M source) {
        for (Map.Entry<Set<M>, O> entry : map.entrySet()) {
            for (M key : entry.getKey()) {
                if (key.equals(source)) {
                    map.remove(entry.getKey());
                }
            }
        }
	}

	/**
	 * Removes the given target from the relation. All the sources that are
	 * pointing to this target are also removed.
	 *
	 * If you take the "result" of {@link #getSources(Object)} and after that
	 * call this method then {@link #containsSource(Object)} will return
	 * <code>false</code> for every object in "result".
	 *
	 * @param target
	 */
	public void disconnect(O target) {
        for (Map.Entry<Set<M>, O> entry : map.entrySet()) {
            if (entry.getValue().equals(target)) {
                map.remove(entry.getKey());
            }
        }
	}

	/**
	 * @return a collection of the targets.
	 */
	public Collection<O> getTargets() {
		return map.values();
	}

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ManyToOneRelation<?, ?> that = (ManyToOneRelation<?, ?>) o;
        return Objects.equals(map, that.map);
    }

    @Override
    public int hashCode() {
        return Objects.hash(map);
    }
}
