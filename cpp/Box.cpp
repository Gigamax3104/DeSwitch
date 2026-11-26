#include	"../h/Box.h"

Box::Box(Vector2Int pos, Vector2 scale, Vector2 boxSize, double angle, std::vector<std::string> imageFile, std::vector<std::string> movieFile, int color, bool transFlag)
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

	int px = int(m_boxSize.x * m_scale.x / 2);
	int py = int(m_boxSize.y * m_scale.y / 2);

	DrawBox(m_pos.x - px, m_pos.y - py, m_pos.x + px, m_pos.y + py, m_color.color, m_color.transparent);
}

bool Box::CheckHit(int posX, int posY, double sizeX, double sizeY) {
	return
		pow(m_pos.x - posX, 2) <= pow(m_boxSize.x + sizeX, 2) && pow(m_pos.y - posY, 2) <= pow(m_boxSize.y + sizeY, 2);
}

bool Box::CheckHit(Vector2Int pos, Vector2 size) {
	return
		m_pos.x - pos.x <= m_boxSize.x + size.x && m_pos.y - pos.y <= m_boxSize.y + size.y;
}

bool Box::CheckHit(const Box& other) {
	if (CheckImageIndex() && m_image[m_image_index].CheckImageData()) {
		if (other.CheckImageIndex() && other.m_image[other.m_image_index].CheckImageData()) {
			Vector2 dir = { pow(m_pos.x - other.m_pos.x, 2), pow(m_pos.y - other.m_pos.y, 2) };

			Vector2Int image1_size = HalfImageSize();
			Vector2Int image2_size = other.HalfImageSize();
			Vector2 r = { pow(image1_size.x + image2_size.x, 2), pow(image1_size.y + image2_size.y, 2) };

			return
				dir.x <= r.x && dir.y <= r.y;
		}
		else {
			Vector2 dir = { pow(m_pos.x - other.m_pos.x, 2), pow(m_pos.y - other.m_pos.y, 2) };

			Vector2Int image_size = HalfImageSize();
			Vector2 box_size = other.m_boxSize.Half();
			Vector2 r = { pow(image_size.x + box_size.x, 2), pow(image_size.y + box_size.y, 2) };

			return
				dir.x <= r.x && dir.y <= r.y;
		}
	}
	else {
		if (other.CheckImageIndex() && other.m_image[other.m_image_index].CheckImageData()) {
			Vector2 dir = { pow(m_pos.x - other.m_pos.x, 2), pow(m_pos.y - other.m_pos.y, 2) };

			Vector2Int image_size = other.HalfImageSize();
			Vector2 box_size = m_boxSize.Half();
			Vector2 r = { pow(image_size.x + box_size.x, 2), pow(image_size.y + box_size.y, 2) };

			return
				dir.x <= r.x && dir.y <= r.y;
		}
		else {
			Vector2 dir = { pow(m_pos.x - other.m_pos.x, 2), pow(m_pos.y - other.m_pos.y, 2) };

			Vector2 box1_size = m_boxSize.Half();
			Vector2 box2_size = other.m_boxSize.Half();
			Vector2 r = { pow(box1_size.x + box2_size.x, 2), pow(box1_size.y + box2_size.y, 2) };

			return
				dir.x <= r.x && dir.y <= r.y;
		}
	}

	return false;
}