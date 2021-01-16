#include <stdio.h>
#include <time.h>

#include "util.hpp"

int main() {
	printf("Hello simulacra!\n");
	
	int width = 1000;
	int height = 1000;
	
	printf("Initializing World...\n");
	
	world w(width, height, 5);
	
	char* timbuf = new char[8];
	
	w.timestr(timbuf);
//	printf("It's %s!\n", timbuf);
	
	delete[] timbuf;
	
	printf("Generating terrain...\n");
	
	pattern2 tmp(width, height);
	
	// Generate terrain
	pattern2 t2(width, height);
	pattern2 t4(width, height);
	pattern2 t8(width, height);
	
	procedural proc;
	
	proc.init(clock());
	
	proc.simplex(t2, 2 , 2 , 0, 0);
	proc.simplex(t4, 6 , 6 , 2, 2);
	proc.simplex(t8, 14, 14, 6, 6);
	
	w.ter.paint(t2, 0.2, 0, 0);
	w.ter.scale(t4, 0, 0);
	w.ter.scale(t8, 0, 0);
	
	w.ter.fit_values();
	
	printf("Generating trees...\n");
	
	// Generate trees
	proc.simplex(tmp, 14, 14, 20, 20);
	for (int i = 0; i < width*height; i++) {
		w.tre.data[i] = (rand() % int(tmp.data[i]*(width/20)) == 0) ? 1 : 0;
	}
	tmp.range(w.ter, 0.22, 0.58);
	w.tre.scale(tmp, 0, 0);
	
	printf("Generating Highways...\n");
	
	// Generate highways
	w.rte.fill(0);
	int hdis = width / 10;
	int i = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x % (hdis/2) == 0 || y % (hdis/2) == 0 || (x+y) % hdis/2 == 0 || (x-y) % hdis/2 == 0) {
				w.rte.data[i] = 1;
			}
			
			i++;
		}
	}
	
	printf("World Generation complete.\n");
	
	printf("Performing Pathfinding test...\n");
	
	float start = (float) clock() / CLOCKS_PER_SEC;
	
	int sx = 20; int sy = 20;
	int ex = 200; int ey = 200;
	pattern2 pth = w.a_star(sx, sy, ex, ey);
	
	float end = (float) clock() / CLOCKS_PER_SEC;
	
	printf("Complete in %.2fs\n", end-start);
	
	int px = sx; int py = sy;
	int nx; int ny;
	float m;
	pattern2 fin(width, height, 0);
	for (int i = 0; i < 1000; i++) {
		fin.data[px+py*width] = 1;
		
		m = 100000;
		for (int x = px-1; x <= px+1; x++) {
			if (x < 0) continue;
			for (int y = py-1; y <= py+1; y++) {
				if (y < 0) continue;
				
				if (pth.data[x+y*width] < m) {
					m = pth.data[x+y*width];
					nx = x;
					ny = y;
				}
			}
		}
		
		if (nx == px && ny == py) {
			printf("Invalid path :(\n");
		}
		
		if (nx == ex && ny == ey) {
			printf("Valid path :) !\n");
			break;
		}
		
		px = nx; py = ny;
	}
	
	fin.saveppm("final_path.ppm");
	
	for (int i = 0; i < width*height; i++) {
		if (pth.data[i] == 100000) {
			pth.data[i] = 0;
		}
	}
	pth.fit_values();
	pth.saveppm("path.ppm");
	
	// Save maps
	w.ter.saveppm("maps/ter.ppm");
	w.tre.saveppm("maps/tre.ppm");
	w.rte.saveppm("maps/rte.ppm");
	
	return 0;
}
