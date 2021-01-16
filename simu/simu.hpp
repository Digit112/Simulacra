// This class represents a person in the simulation. They have a personality, skills, needs, and desires among other things.
class simu {
public:
	// World this simu lives in
	world* w = NULL;
	
	// Basic needs run from 0 to 1
	float food = 1; // Amount of food. At 0, the simu begins to take damage.
	float water = 1; // Amoujnt of water. At 0, the simu begins to take damage.
	float energy = 1; // Represents tiredness. Character spontaneously falls unconsciences when energy reaches 0.
	float social = 1; // Represents need for social contact. A low social score amounts to a degredation in mental state and drives the simu to find others.
	float health = 1; // Represents physical health. Affected by age, illness, hunger, etc. When it reaches 0 the simu dies.
	
	// Degree of illness. Increases damage to character. Increases around other ill people or when working.
	// Decreases when treated, rested, and well fed.
	// Increases damage taken and reduces ability to work as well as travel speed. Health steadily reduces when ill.
	float illness = 0;
	
	// Age in months. Effects skill caps at a low age and travel speed among other things.
	int age = 0;
	
	// Physical attributes.
	float strength = 0.5; // Changes rate of task completion and skill in combat.
	float endurance = 0.5; // Modifies rate of task completion and rate of fatigue gain.
	float intelligence = 0.5; // Modifies skill improvement rate.
	float will = 0.5; // Effects this character's suceptibility to mental degradation under stress
	float fortitude = 0.5; // Reduces this character's loss of strength due to fatigue and suceptibility to illness.
	
	// Mental attributes. Most of these modify the choices the simu makes directly and modify the way their emotional state changes as well.
	float optimism = 0.5;
	float compassion = 0.5;
	float patience = 0.5;
	
	float anxiety = 0.5;
	float deppression = 0.5;
	
	// This simu's gender and who they are capable of forming romantic relationships with.
	enum gend {MALE = 0, FEMALE = 1};
	enum sexu {GAY = 0, STRAIGHT = 1, BISEXUAL = 2, ASEXUAL = 3};
	
	gend gender = MALE;
	sexu sexuality = STRAIGHT;
	
	// Represents skills. Skills are effectively 0 until they reach "basic" level.
	// Level Guide: basic - 0.15, novice - 0.30, apprentice - 0.45, adept - 0.60, expert - 0.75, master - 0.90
	// Skills increase on a logistic curve, making subsequent levels harder to reach. Note - levels are semantic, only the exact number matters
	
	// Moving around. Effects Travel speeds.
	float swimming = 0; // Liability to drown and travel speed while swimming.
	float travel = 0; // Travel speed by foot.
	float equestrian = 0; // Travel speed by horse.
	
	// Getting food. Effects the rate at which food is acquired while hunting, fishing, and foraging.
	float hunting = 0; // Skill in hunting animals.
	float fishing = 0; // Skill in fishing for food.
	float foraging = 0; // Skill in foraging for food such as berries and fruits.
	
	float farming = 0; // Skill in maintaining a grain farm for food.
	float orcharding = 0; // Skill in maintaining an orchard for food.
	float ranching = 0; // Skill in maintaining livestock.
	
	// Creating things. Skill effects speed of creation, material efficiency, durability and effectiveness of the creation.
	float construction = 0; // Skill in building structures.
	float crafting = 0; // Ability to create tools, clothes, weapons, and armor without the proper equipment. (This is how the first tribes get their crude equipment)
	float smithing = 0; // Ability to use a forge for creating tools, weapons, and armor.
	float fletching = 0; // Ability to create arrows and, although it doesn't exactly track with the word "fletching", ability to create bows.
	float tailoring = 0; // Ability to make clothes.
	
	// Fighting. Effects ability in various combat scenarios.
	float unaramed = 0; // Skill in unarmed, hand to hand combat.
	float armed = 0; // Skill in melee armed combat.
	float ranged = 0; // Skill in combat using a bow.
	
	// Randomly generate this simu.
	void generate(int age_min, int age_max);
	
	// Calculate desire
	float food_desire();
	float water_desire();
	float sleep_desire();
	float social_desire();
	
	// Calculate Stress
	float stress();
};

#include "simu.cpp"
