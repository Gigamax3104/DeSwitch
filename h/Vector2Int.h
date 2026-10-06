#pragma once
#include	<math.h>

class Vector2Int {
public:
	int x;
	int y;

	Vector2Int() : x(0), y(0) {}
	Vector2Int(int x, int y) : x(x), y(y) {}
	Vector2Int(const Vector2Int& value) : x(value.x), y(value.y) {}

	Vector2Int operator-() const { return Vector2Int(-x, -y); }

	Vector2Int operator+(int value) const { return Vector2Int(x + value, y + value); }
	Vector2Int operator-(int value) const { return Vector2Int(x - value, y - value); }
	Vector2Int operator*(int value) const { return Vector2Int(x * value, y * value); }
	Vector2Int operator/(int value) const { return Vector2Int(x / value, y / value); }

	Vector2Int operator+(const Vector2Int& value) const { return Vector2Int(x + value.x, y + value.y); }
	Vector2Int operator-(const Vector2Int& value) const { return Vector2Int(x - value.x, y - value.y); }
	Vector2Int operator*(const Vector2Int& value) const { return Vector2Int(x * value.x, y * value.y); }
	Vector2Int operator/(const Vector2Int& value) const { return Vector2Int(x / value.x, y / value.y); }

	void operator=(const Vector2Int& value) { x = value.x; y = value.y; }
	void operator=(int value) { x = value; y = value; }

	void operator+=(int value) { x += value; y += value; }
	void operator-=(int value) { x -= value; y -= value; }
	void operator*=(int value) { x *= value; y *= value; }
	void operator/=(int value) { x /= value; y /= value; }

	void operator+=(const Vector2Int& value) { x += value.x; y += value.y; }
	void operator-=(const Vector2Int& value) { x -= value.x; y -= value.y; }
	void operator*=(const Vector2Int& value) { x *= value.x; y *= value.y; }
	void operator/=(const Vector2Int& value) { x /= value.x; y /= value.y; }

	bool operator==(int value) { return x == value && y == value; }
	bool operator==(const Vector2Int& value) { return x == value.x && y == value.y; }

	bool operator!=(int value) { return x != value && y != value; }
	bool operator!=(const Vector2Int& value) { return x != value.x && y != value.y; }

	const Vector2Int Half() { return Vector2Int(x / 2, y / 2); }

	void Normalize() { double norm = Norm(); if (norm > 0.0) { x /= (int)norm; y /= (int)norm; } }

	static double Dot(const Vector2Int& v1, const Vector2Int& v2) { return v1.x * v2.x + v1.y * v2.y; }

	void ZeroReset() { x = 0; y = 0; }

private:
	double Norm() { return sqrt(pow(x + y, 2)); }
};

//Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2) { return Vector2Int(v1.x + v2.x, v1.y + v2.y); }
//Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2) { return Vector2Int(v1.x - v2.x, v1.y + v2.y); }
//Vector2Int operator*(const Vector2Int& v1, const Vector2Int& v2) { return Vector2Int(v1.x * v2.x, v1.y * v2.y); }
//
//Vector2Int operator*(const Vector2Int& value, double scaler) { return Vector2Int(value.x * scaler, value.y * scaler); }
//Vector2Int operator*(double scaler, const Vector2Int& value) { return Vector2Int(value.x * scaler, value.y * scaler); }