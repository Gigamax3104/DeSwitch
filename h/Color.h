#pragma once
#define	RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define ORANGE 0xf08300
#define YELLOW 0xffd900
#define PURPLE 0x8e4898
#define BLACK 0x000000
#define WHITE 0xffffff

class Color {
public:
	int color;
	bool transparent;

	Color() : color(WHITE), transparent(true){}
	Color(int color_code, bool trans = true) : color(color_code), transparent(trans){}
	Color(const Color& other) : color(other.color), transparent(other.transparent){}

	void operator=(const Color& other) { color = other.color; transparent = other.transparent; }

	bool operator==(const Color& other) { return color == other.color && transparent == other.transparent; }
	bool operator!=(const Color& other) { return color != other.color && transparent != other.transparent; }
};