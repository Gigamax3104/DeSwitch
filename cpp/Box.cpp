#include	"../h/Box.h"

Box::Box(Vector2Int pos, Vector2 size, Vector2 scale, int color, double angle, bool transFlag, std::string imageFile, std::string movieFile)
: GameObject(pos, scale, angle, imageFile, movieFile),m_size(size),m_color(color,transFlag){}

Box::Box(GameObject obj, Vector2 size, int color, bool transFlag, std::string imageFile, std::string movieFile)
 : GameObject(obj),m_size(size), m_color(color, transFlag){
	m_image.SetImage(imageFile);
	m_movie.SetMovie(movieFile);
}

Box::Box(GameObject obj, Vector2 size, Color color, std::string imageFile, std::string movieFile)
	: GameObject(obj),m_size(size),m_color(color){
	m_image.SetImage(imageFile);
	m_movie.SetMovie(movieFile);
}

void Box::operator=(const Box& other) {
	if (this != &other) {
		GameObject::operator=(other);
		m_size = other.m_size;
		m_color = other.m_color;
	}
}

void Box::Display() {
	GameObject::Display();

	DrawBox(m_pos.x - (int)m_size.Half().x * (int)m_scale.x, m_pos.y - (int)m_size.Half().y * (int)m_scale.y,
		m_pos.x + (int)m_size.Half().x * (int)m_scale.x, m_pos.y + (int)m_size.Half().y * (int)m_scale.y, m_color.color, m_color.transparent);
}

bool Box::CheckHit(int posX, int posY, double sizeX, double sizeY) {
	return
		pow(m_pos.x - posX, 2) <= pow(m_size.x + sizeX, 2) && pow(m_pos.y - posY, 2) <= pow(m_size.y + sizeY, 2);
}

bool Box::CheckHit(Vector2Int pos, Vector2 size) {
	return
		pow(m_pos.x - pos.x, 2) <= pow(m_size.x + size.x, 2) && pow(m_pos.y - pos.y, 2) <= pow(m_size.y + size.y, 2);
}

bool Box::CheckHit(const Box& other) {
	return
		pow(m_pos.x - other.m_pos.x, 2) <= pow(m_size.x + other.m_size.x, 2)
		&& pow(m_pos.y - other.m_pos.y, 2) <= pow(m_size.y + other.m_size.y, 2);
}