float rval() {
	return (float) (rand() % 10000) / 10000;
}

void simu::generate(int age_min, int age_max) {
	float r;
	
	food = 1;
	water = 1;
	energy = 1;
	social = 1;
	health = 1;
	
	illness = 0;
	
	age = rand() % (age_max - age_min) + age_min;
	
	strength = rval();
	endurance = rval();
	intelligence = rval();
	will = rval();
	fortitude = rval();
	
	optimism = rval();
	anxiety = rval();
	deppression = rval();
	
	r = rval();
	if (r < 0.5) {
		gender = MALE;
	}
	else {
		gender = FEMALE;
	}
	
	r = rval();
	if (r < 0.05) {
		sexuality = ASEXUAL;
	}
	else if (r < 0.1) {
		sexuality = BISEXUAL;
	}
	else if (r < 0.55) {
		sexuality = STRAIGHT;
	}
	else {
		sexuality = GAY;
	}
}
