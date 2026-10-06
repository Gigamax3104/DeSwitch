#include	"../h/Human.h"

Human::Human(const Human& other) : GameObject(other){
	name = other.name;
	jender = other.jender;
	height = other.height;
	weight = other.weight;
	for(int i = 0; i < 3; i++) birthday[i] = other.birthday[i];
	m_job = other.m_job;
}

void Human::operator=(const Human& other) {
	if (this != &other) {
		GameObject::operator=(other);

		name = other.name;
		jender = other.jender;
		height = other.height;
		weight = other.weight;
		for (int i = 0; i < 3; i++) birthday[i] = other.birthday[i];
		m_job = other.m_job;
	}
}

void Human::Set(std::string myName, std::string myJender, double myHeight, double myWeight, int myBirthday[], std::string jobName) {
	name = myName;
	jender = myJender;
	height = myHeight;
	weight = myWeight;
	m_job = jobName;

	int myBirthdaySize = sizeof myBirthday / sizeof myBirthday[0];
	if (myBirthdaySize != sizeof birthday / sizeof birthday[0] || myBirthdaySize == 0) return;

	for(int i = 0; i < myBirthdaySize; i++) birthday[i] = myBirthday[i];
}