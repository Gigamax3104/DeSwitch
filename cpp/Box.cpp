#include	"../h/Box.h"

Box::Box(Vector2Int pos, Vector2 boxSize, Vector2 scale, int color, double angle, bool transFlag, std::vector<std::string> imageFile, std::vector<std::string> movieFile)
: GameObject(pos, scale, angle, imageFile, movieFile),m_boxSize(boxSize),m_color(color,transFlag){}

Box::Box(GameObject obj, Vector2 boxSize, int color, bool transFlag)
: GameObject(obj),m_boxSize(boxSize), m_color(color, transFlag){}

Box::Box(GameObject obj, Vector2 boxSize, Color color)
	: GameObject(obj), m_boxSize(boxSize),m_color(color){}

void Box::operator=(const Box& other) {
	if (this != &other) {
		GameObject::operator=(other);
		m_boxSize = other.m_boxSize;
		m_color = other.m_color;
	}
}

void Box::Display() {
	GameObject::Display();

	DrawBox(m_pos.x - (int)m_boxSize.Half().x * (int)m_scale.x, m_pos.y - (int)m_boxSize.Half().y * (int)m_scale.y,
		m_pos.x + (int)m_boxSize.Half().x * (int)m_scale.x, m_pos.y + (int)m_boxSize.Half().y * (int)m_scale.y, m_color.color, m_color.transparent);
}

bool Box::CheckHit(int posX, int posY, double sizeX, double sizeY) {
	return
		pow(m_pos.x - posX, 2) <= pow(m_boxSize.x + sizeX, 2) && pow(m_pos.y - posY, 2) <= pow(m_boxSize.y + sizeY, 2);
}

bool Box::CheckHit(Vector2Int pos, Vector2 size) {
	return
		pow(m_pos.x - pos.x, 2) <= pow(m_boxSize.x + size.x, 2) && pow(m_pos.y - pos.y, 2) <= pow(m_boxSize.y + size.y, 2);
}

bool Box::CheckHit(const Box& other) {
	return
		pow(m_pos.x - other.m_pos.x, 2) <= pow(m_boxSize.x + other.m_boxSize.x, 2)
		&& pow(m_pos.y - other.m_pos.y, 2) <= pow(m_boxSize.y + other.m_boxSize.y, 2);
}