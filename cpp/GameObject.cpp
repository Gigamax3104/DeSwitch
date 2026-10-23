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

GameObject::GameObject(Vector2Int pos, Vector2 size, double angle, std::vector<std::string> imageFile, std::vector<std::string> movieFile)
 : m_pos(pos), m_scale(size),m_angle(angle) {
	if (!imageFile.empty()) {
		m_image_size = imageFile.size();
		m_image = new Image[m_image_size];

		for (int i = 0; i < m_image_size; i++)
			if (imageFile[i] != "\0") {
				m_image[i] = imageFile[i];
			}
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

void GameObject::Display() {
	for (int i = 0; i < m_image_size; i++) {
		if (m_image[i].CheckImageData()) {
			if (m_scale != 0.0) {
				m_image[i].ExDraw(m_pos, m_scale);
				return;
			}
			else {
				m_image[i].Draw(m_pos);
				return;
			}
		}
	}

	for (int i = 0; i < m_movie_size; i++) {
		if (m_movie[i].CheckMovieData()) {
			if (m_scale != 0.0) {
				m_image[i].ExDraw(m_pos, m_scale); return;
			}
			else {
				m_movie[i].ExPlay(m_pos, m_scale);
				return;
			}
		}
	}
}

GameObject::~GameObject() {
	if (m_image != nullptr) { delete[] m_image; m_image = nullptr; }
	if (m_movie != nullptr) { delete[] m_movie; m_movie = nullptr; }
}