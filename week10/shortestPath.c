double shortestPath(Graph graph, int s, int t, int* path, double* length) {
  if (graph.edges == NULL || graph.vertices == NULL)
    return INFINITE_VALUE;

  if (path == NULL || length == NULL)
    return INFINITE_VALUE;

  int i, max_id = getHighestID(graph);
  double *dist = malloc(sizeof(double) * (max_id + 1));  // free ?
  int *prev = malloc(sizeof(int) * (max_id + 1));
  if (!dist || !prev) {
    fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
    exit(1);
  }

  Dllist queue = new_dllist();   // free ?

  for (i = 0; i <= max_id ; ++i) {
    if (i != s) {
      dist[i] = INFINITE_VALUE;
      prev[i] = UNDEFINED;
    }
    dll_append(queue, new_jval_i(i));
  }

  dist[s] = 0;

  while (!dll_empty(queue)) {
    // extract min
    int u;
    {
      Dllist tmp, min_node = dll_first(queue);
      int min = jval_i(dll_first(queue)->val);
      dll_traverse(tmp, queue) {
        int tmp_node_i = jval_i(tmp->val);
        if (dist[min] > dist[tmp_node_i]) {
          min = tmp_node_i;
          min_node = tmp;
        }
      }
      u = min;
      dll_delete_node(min_node);
    }

    //
    int *out_degree_u_list = malloc(sizeof(int) * (max_id + 1));  // free ?
    if (!out_degree_u_list) {
      fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
      exit(1);
    }
    int out_degree_u = outdegree(graph, u, out_degree_u_list);
    if (out_degree_u == 0)
      continue;

    int i;
    for (i = 0; i < out_degree_u; i++) {
      int v = out_degree_u_list[i];
      double alt = dist[u] + getWeight(graph, u, v);
      if (alt < dist[v]) {
        dist[v] = alt;
        prev[v] = u;
        dll_append(queue, new_jval_i(v));
      }

    }
    // free(out_degree_u_list);

  }

  for (i = 0; i <= max_id + 1; i++) {
    length[i] = dist[i];
  }

  if (prev[t] != -1) {
    int j = 1;
    path[0] = t;
    while (1) {
      path[j] = prev[path[j - 1]];
      if (path[j] == s)
        break;
      j++;
    }
    path[++j] = -1;
  }
  
  free_dllist(queue);
  free(dist);
  free(prev);

  return dist[t];
}








double shortestPath(Graph g, int s, int t, int * path, int * length) {
    JRB node = jrb_find_int(g.vertices, s);
    JRB distance = make_jrb();
    JRB parent = make_jrb();
    Dllist queue = new_dllist();
    int count = 0;

    if (node == NULL) {
        printf("There is no node %d in the graph.\n" ,s);
        return INFINITIVE_VALUE;
    }

    jrb_traverse(node, g.vertices) {
        int key = jval_i(node->key);
        double dist = INFINITIVE_VALUE;
        if (key == s) {
            dist = 0;
        }
        jrb_insert_int(distance, key, new_jval_d(dist));
        jrb_insert_int(parent, key, new_jval_i(-1));
    }

    jrb_traverse(node, g.vertices) {
        int key = jval_i(node->key);
        if (key == s) {
            dll_prepend(queue, new_jval_i(key));
        } else {
            dll_append(queue, new_jval_i(key));
        }
    }

    while(dll_empty(queue) != 1) {
        Dllist temp = dll_first(queue);
        int key = jval_i(temp->val);
        int adjacents[100];
        int i, total;
        int weight, toKey, toAdj;
        int adjKey;

        if (key == t) {
            i = total = 0;
            // Look up the node t in parent, return it's value to * path
            while(key != -1) {
                // Use adjacents[] as a middle array,
                // since the way we traverse will return the
                // node in reverse order
                adjacents[total] = key;
                total++;
                key = jval_i(jrb_find_int(parent, key)->val);
            }
            for (i = 0; i < total; i++) {
                path[i] = adjacents[total - 1 - i];
            }
            // Return the total route to * length
            *length = total;
            // Return the total weight;  
            return jval_d(jrb_find_int(distance, t)->val);
        }

        // Dequeue the first element
        dll_delete_node(temp);

        // Distance to it from the start node
        toKey = jval_d(jrb_find_int(distance, key)->val);

        total = outdegree(g, key, adjacents);
        for (i = 0; i < total; i++) {
            adjKey = adjacents[i];
            weight = getEdgeValue(g, key, adjKey);
            toAdj = jval_d(jrb_find_int(distance, adjKey)->val);
            
            // If the path to the adjacent node can be shorten
            // by going through the current node,
            // we set its parent to the current node
            if (toKey + weight < toAdj) {
                node = jrb_find_int(distance, adjKey);
                jrb_delete_node(node);
                jrb_insert_int(distance, adjKey, new_jval_d(toKey + weight));
                
                node = jrb_find_int(parent, adjKey);
                jrb_delete_node(node);
                jrb_insert_int(parent, adjKey, new_jval_i(key));

                // Dequeue the adjacent node and re-add it
                // to maintain the priority
                dll_traverse(temp, queue) {
                    if (jval_i(temp->val) == adjKey) {
                        dll_delete_node(temp);
                        break;
                    }
                }
                toAdj = toKey + weight;
                dll_traverse(temp, queue) {
                    int qKey = jval_i(temp->val);
                    int dist = jval_d(jrb_find_int(distance, qKey)->val);
                    if (dist > toAdj) {
                        dll_insert_b(temp, new_jval_i(adjKey));
                        break;
                    }
                }
            }
        }
    }
    
    return INFINITIVE_VALUE;
}