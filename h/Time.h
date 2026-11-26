#pragma once
#include	"DxLib.h"

const int COUNT = 100; //3•bƒJƒEƒ“ƒg

class Time {
public:
	static int frame;
	static double deltatime;

	static void Init() { m_nowTime = GetNowCount(); }
	static void Update() { frame++;  m_lastTime = m_nowTime; m_nowTime = GetNowCount(); deltatime = (m_nowTime - m_lastTime) / 1000.0; }

private:
	static double m_lastTime;
	static double m_nowTime;
};