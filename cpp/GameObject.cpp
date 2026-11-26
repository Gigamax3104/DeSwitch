#include	"../h/GameObject.h"

GameObject::GameObject(int posX, int posY, double sizeX, double sizeY, double angle, std::vector<std::string> imageFile, std::vector<std::string> movieFile)
 : m_pos(posX, posY), m_scale(sizeX, sizeY),m_angle(angle) {
	if (!imageFile.empty()) {
		m_image_size = imageFile.size();
		m_image = new Image[m_image_size];

		for (int i = 0; i < m_image_size; i++)
			if (imageFile[i] != "\0") m_image[i].SetImage(imageFile[i]);
	}

	if (!movieFile.empty()) {
		m_movie_size = movieFile.size();
		m_movie = new Movie[m_movie_size];

		for (int i = 0; i < m_movie_size; i++)
			if (movieFile[i] != "\0") m_movie[i].SetMovie(movieFile[i]);
	}
}

GameObject::GameObject(Vector2Int pos, Vector2 scale, double angle, std::vector<std::string> imageFile, std::vector<std::string> movieFile)
 : m_pos(pos), m_scale(scale),m_angle(angle) {
	if (!imageFile.empty()) {
		m_image_size = imageFile.size();
		m_image = new Image[m_image_size];

		for (int i = 0; i < m_image_size; i++)
			if (imageFile[i] != "\0") m_image[i] = imageFile[i];
	}

	if (!movieFile.empty()) {
		m_movie_size = movieFile.size();
		m_movie = new Movie[m_movie_size];

		for (int i = 0; i < m_movie_size; i++)
			if (movieFile[i] != "\0") m_movie[i] = movieFile[i];
	}
}

GameObject::GameObject(const GameObject& other)
	: m_pos(other.m_pos), m_scale(other.m_scale), m_angle(other.m_angle),m_image_size(other.m_image_size),m_movie_size(other.m_movie_size),
	m_image(new Image[other.m_image_size]),m_movie(new Movie[other.m_movie_size]) {
	for (int i = 0; i < m_image_size; i++)
		if (other.m_image[i].CheckImageData()) m_image[i] = other.m_image[i];

	for (int i = 0; i < m_movie_size; i++)
		if (other.m_movie[i].CheckMovieData())m_movie[i] = other.m_movie[i];
}

void GameObject::operator=(const GameObject& other) {
	m_pos = other.m_pos;
	m_scale = other.m_scale;
	m_angle = other.m_angle;
	m_image_size = other.m_image_size;
	m_movie_size = other.m_movie_size;

	if (m_image != nullptr) { delete[] m_image; m_image = nullptr; }
	if (m_movie != nullptr) { delete[] m_movie; m_movie = nullptr; }
	
	m_image = new Image[m_image_size];
	m_movie = new Movie[m_movie_size];
	for(int i = 0; i < m_image_size; i++) if (other.m_image[i].CheckImageData()) m_image[i] = other.m_image[i];
	for(int i = 0; i < m_movie_size; i++) if (other.m_movie[i].CheckMovieData()) m_movie[i] = other.m_movie[i];
}

const Vector2Int GameObject::HalfImageSize() const {
	return
		Vector2Int(int(m_image[m_image_index].Get_ImageGraphSize().x * m_scale.x / 2),
			int(m_image[m_image_index].Get_ImageGraphSize().y * m_scale.y / 2));
}

const Vector2Int GameObject::HalfMovieSize() const {
	return
		Vector2Int(int(m_movie[m_movie_index].Get_MovieGraphSize().x * m_scale.x / 2),
			int(m_movie[m_movie_index].Get_MovieGraphSize().y * m_scale.y / 2));
}

void GameObject::Display() {
	switch (m_graphFlag) {
	case IMAGE:
		if (m_image[m_image_index].CheckImageData()) {
			if (m_scale != 0.0) {
				m_image[m_image_index].ExDraw(m_pos, m_scale);
				return;
			}
			else {
				m_image[m_image_index].Draw(m_pos);
				return;
			}
		}
		break;

	case MOVIE:
		if (m_movie[m_movie_index].CheckMovieData()) {
			if (m_scale != 0.0) {
				m_movie[m_movie_index].ExPlay_Scale(m_pos, m_scale);
				return;
			}
			else {
				m_movie[m_movie_index].Play(m_pos);
				return;
			}
		}
		break;
	}
}

GameObject::~GameObject() {
	if (m_image != nullptr) { delete[] m_image; m_image = nullptr; }
	if (m_movie != nullptr) { delete[] m_movie; m_movie = nullptr; }
}