class as_node {
public:
	int x;
	int y;
	float heu;
	
	as_node();
	as_node(int, int, float);
};

class world {
public:
	// Time since the start of day in seconds. Initialized to 6:00am. (There are 86,400 seconds in a day)
	int time = 21600;
	
	int width;
	int height;
	
	pattern2 ter;
	pattern2 tre;
	pattern2 rte;
	
	darray<simu> simus;
	
	world(int width, int height, int pop);
	
	// Copies into the given buffer the time in a readable format.
	char* timestr(char* buf);
	
	// Produces a weightmap between the two locations on the map using only pure A*.
	pattern2 a_star(int sx, int sy, int ex, int ey);
};

#include "world.cpp"
