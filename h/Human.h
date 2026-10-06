#pragma once
#include	"GameObject.h"

class Human : public GameObject {
public:
	std::string name;
	std::string jender;

	double height;
	double weight;

	enum BIRTHDAY{ YEAR, MONTH, DAY };
	int birthday[3];

	Human() : GameObject() { name = ""; jender = ""; height = 0.0; weight = 0.0; for (int i = 0; i < 3; i++) birthday[i] = 0; }
	Human(const Human& other);

	void operator=(const Human& other);

	void ChangeJob(std::string job_name) { m_job = job_name; }
	const std::string GetMyJob() const { return m_job; }

	void Set(std::string myName = "", std::string myJender = "", double myHeight = 0.0, double myWeight = 0.0, int myBirthday[] = {}, std::string jobName = "");
protected:
	std::string m_job;
};