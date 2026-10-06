#include	"../h/GameObject.h"

GameObject::GameObject(int posX, int posY, double sizeX, double sizeY, double angle, std::string imageFile, std::string movieFile)
 : m_pos(posX, posY), m_scale(sizeX, sizeY),m_angle(angle),m_image(NULL),m_movie(NULL){
	if (imageFile != "\0") m_image = Image(imageFile);
	if (movieFile != "\0") m_movie = Movie(movieFile);
}

GameObject::GameObject(Vector2Int pos, Vector2 size, double angle, std::string imageFile, std::string movieFile)
 : m_pos(pos), m_scale(size),m_angle(angle), m_image(NULL), m_movie(NULL) {
	if (imageFile != "\0") m_image = Image(imageFile);
	if (movieFile != "\0") m_movie = Movie(movieFile);
}

GameObject::GameObject(const GameObject& other) : m_pos(other.m_pos), m_scale(other.m_scale), m_angle(other.m_angle),m_image(NULL), m_movie(NULL) {
	if (other.m_image.Get_ImageData().GetImageFile() != -1) m_image = Image(other.m_image.Get_ImageData().GetFileName());
}

void GameObject::operator=(const GameObject& other) {
	m_pos = other.m_pos;
	m_scale = other.m_scale;
	m_angle = other.m_angle;
	m_image = other.m_image;
	m_movie = other.m_movie;
}

void GameObject::Display() {
	if (m_scale != 0.0) { if (m_image.Get_ImageData().CheckSetImageFile()) m_image.ExDraw(m_pos, m_scale); return; }
	else { if (m_image.Get_ImageData().CheckSetImageFile()) m_image.Draw(m_pos); return; }

	if (m_scale != 0.0) { if (m_image.Get_ImageData().CheckSetImageFile()) m_image.ExDraw(m_pos, m_scale); return; }
	else { if (m_movie.Get_MovieData().CheckSetMovieFile()) m_movie.ExPlay(m_pos, m_scale); return; }
}