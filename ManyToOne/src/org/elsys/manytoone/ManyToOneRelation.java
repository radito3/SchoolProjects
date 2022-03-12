package org.elsys.manytoone;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

/**
 * Introduces the notation of many-to-one relation. This is where the M and O of
 * the type signature comes from.
 * <p>
 * Many unique "source" objects refer to one and only "target" object.
 * <p>
 * The class maintains a connection between the target and all the sources that
 * are referring to it.
 *
 * @param <M> the type of the "source" objects.
 * @param <O> the type of the "target" objects.
 * @author Kiril Mitov k.mitov@sap.com
 */
public class ManyToOneRelation<M, O> {

    private final Map<O, Set<M>> map;

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
        Set<M> prevSources = map.get(target);
        if (prevSources == null) {
            map.put(target, new HashSet<>(Collections.singleton(source)));
            return true;
        }
        prevSources.clear();
        return prevSources.add(source);
    }

    /**
     * @param source
     * @return <code>true</code> if the relation contains the given source
     */
    public boolean containsSource(M source) {
        return map.values()
				  .stream()
				  .anyMatch(sources -> sources.contains(source));
    }

    /**
     * @param target
     * @return <code>true</code> if the relation contains the given target
     */
    public boolean containsTarget(O target) {
        return map.containsKey(target);
    }

    /**
     * @param source
     * @return the target with which this source is connected
     */
    public O getTarget(M source) {
        for (Map.Entry<O, Set<M>> entry : map.entrySet()) {
            if (entry.getValue().contains(source)) {
                return entry.getKey();
            }
        }
        return null;
    }

    /**
     * @param target
     * @return all the targets that are connected with this source or empty
     * collection if there are no sources connected with this target.
     */
    public Collection<M> getSources(O target) {
        return map.getOrDefault(target, Collections.emptySet());
    }

    /**
     * Removes the connection between this source and the corresponding target.
     * Other sources will still point to the same target.
     * <p>
     * The target is removed if this was the only source pointing to it and
     * {@link #containsTarget(Object)} will return false.
     *
     * @param source
     */
    public void disconnectSource(M source) {
        for (Iterator<Set<M>> it = map.values().iterator(); it.hasNext(); ) {
            Set<M> sources = it.next();
            sources.remove(source);
            if (sources.isEmpty()) {
                it.remove();
            }
        }
    }

    /**
     * Removes the given target from the relation. All the sources that are
     * pointing to this target are also removed.
     * <p>
     * If you take the "result" of {@link #getSources(Object)} and after that
     * call this method then {@link #containsSource(Object)} will return
     * <code>false</code> for every object in "result".
     *
     * @param target
     */
    public void disconnect(O target) {
        map.remove(target);
    }

    /**
     * @return a collection of the targets.
     */
    public Collection<O> getTargets() {
        return map.keySet();
    }

    @Override
	public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        ManyToOneRelation<?, ?> that = (ManyToOneRelation<?, ?>) o;
        return Objects.equals(map, that.map);
    }

    @Override
	public int hashCode() {
        return Objects.hash(map);
    }
}
