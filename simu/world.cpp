as_node::as_node() {}
as_node::as_node(int x, int y, float heu) : x(x), y(y), heu(heu) {}

world::world(int width, int height, int pop) : time(21600), width(width), height(height), ter(width, height, 0), tre(width, height, 0), rte(width, height), simus(pop) {
	for (int s = 0; s < simus.size; s++) {
		simus[s].generate(16*12, 24*12);
		simus[s].w = this;
	}
}

char* world::timestr(char* buf) {
	char* id = (char*) "am";
	int hour = time / 3600;
	int minute = (time % 3600) / 60;
	if (hour > 12) {
		id[0]='p';
		hour -= 12;
	}
	
	sprintf(buf, "%d:%02d%s", hour, minute, id);
	return buf;
}

pattern2 world::a_star(int sx, int sy, int ex, int ey) {
	// Holds distance weights for each node.
	pattern2 out(width, height, 100000);
	out.data[ex+ey*width] = 0;
	
	// Keeps track of which nodes have been processed
	pattern2 tvl(width, height, 0);
	
	// Priority Queue. The first value is the end node, whose heuristic doesn't matter since that only controls insertion into the queue and this node is removed immediately.
	llist<as_node> pq(as_node(ex, ey, 0));
	
	// The height of the source node
	float salt = ter.data[sx+sy*width];
	
	int iter = -1;
	
	// Take the top item off the priority queue, calculate the heuristic distance for its neighbors, and add them to the queue.
	as_node node; // The node off the priority queue
	while (true) {
//		if (iter > 1000000 || (node.x == 0 && node.y == 0)) return out;
		
		iter++;
		
		// Check that a node to evaluate still exists.
		if (pq.size == 0) {
			printf("Cannot reach destination from here!\n");
			return out;
		}
		
		// Take the top node off the priority queue.
		node = pq[0];
//		printf("Took (%d, %d) from queue of size %d\n", node.x, node.y, pq.size);
		pq.remove(0);
		
		// Calculate index of this node in the patterns
		int ind = node.x+node.y*width;
		
		// Evaluate neighbors
		for (int y = node.y-1; y <= node.y+1; y++) {
			// Don't evaluate out-of-bound nodes
			if (y < 0 || y > height) continue;
			int pitch = y*width;
			for (int x = node.x-1; x <= node.x+1; x++) {
				// Don't treat (x, y) as its own neighbor. Also don't evaluate out-of-bound nodes.
				if ((x == node.x && y == node.y) || x < 0 || x > width) continue;
				
				// Calculate index of (x, y) in the patterns.
				int nind = x+pitch;
				
				bool do_insert = tvl.data[nind] == 0;
				tvl.data[nind] = 1;
				
				// Calculate heuristic for distance from (sx, sy) to (x, y)
				int dx = x-sx;
				int dy = y-sy;
				float heu = 2*fabs((salt-ter.data[nind])/(sqrt(dx*dx+dy*dy)*0.2) + 0.8) + 1;
				
				// Calculate cost of moving from (x, y) to (node.x, node.y)
				int ndx = x-node.x;
				int ndy = y-node.y;
				float step_cost = 2*fabs((ter.data[nind]-ter.data[ind])/(sqrt(ndx*ndx+ndy*ndy)*0.2) + 0.8) + 1;
				
//				printf("(%d, %d) (%d, %d) %f, %f\n", node.x, node.y, x, y, heu, step_cost);
				
				// Add the the step cost and the distance from (node.x, node.y) to (ex, ey) to get the distance from (x, y) to (ex, ey)
				// Use min since there are multiple paths to each node to ensure the lowest value is recorded.
				out.data[nind] = fmin(out.data[ind] + step_cost, out.data[nind]);
				
				// If this node is the source, stop.
				if (x == sx && y == sy) {
					printf("Path found!\n");
					return out;
				}
				
				// Combine that with the heuristic to get the estimated distance from (sx, sy) to (ex, ey) along this route.
				heu += out.data[nind];
				
				// Insert this new node into the priority queue based on its heuristic
				// If the queue is empty, just add it...
				if (pq.size == 0) {
//					printf("Queueing (%d, %d) at 0\n", x, y);
					pq.append(as_node(x, y, heu));
					continue;
				}
				
				// ...otherwise, insert it based on its value, remove it if it is already in the queue and continue.
				int i = 0;
				llist_node<as_node>* cur = pq.first;
				while (true) {
					if (cur->value.x == x && cur->value.y == y) {
						cur = cur->next;
						
						pq.remove(i);
					}
					else {
						if (cur->value.heu > heu && do_insert) {
//							printf("Queueing (%d, %d) at %d\n", x, y, i);
							pq.insert(i, as_node(x, y, heu));
							do_insert = false;
							i++;
						}
						cur = cur->next;
					}
					
					if (cur == NULL) {
						if (do_insert) {
							pq.append(as_node(x, y, heu));
							break;
						}
						else {
							break;
						}
					}
					i++;
				}
			}
		}
	}
}
