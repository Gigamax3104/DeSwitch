#pragma once
#include	<math.h>

class Vector2 {
public:
	double x;
	double y;

	Vector2() : x(0), y(0) {}
	Vector2(double x, double y) : x(x), y(y) {}
	Vector2(const Vector2& value) : x(value.x), y(value.y) {}

	Vector2 operator-() const { return Vector2(-x, -y); }

	Vector2 operator+(double value) const { return Vector2(x + value, y + value); }
	Vector2 operator-(double value) const { return Vector2(x - value, y - value); }
	Vector2 operator*(double value) const { return Vector2(x * value, y * value); }
	Vector2 operator/(double value) const { return Vector2(x / value, y / value); }

	Vector2 operator+(const Vector2& value) const { return Vector2(x + value.x, y + value.y); }
	Vector2 operator-(const Vector2& value) const { return Vector2(x - value.x, y - value.y); }
	Vector2 operator*(const Vector2& value) const { return Vector2(x * value.x, y * value.y); }
	Vector2 operator/(const Vector2& value) const { return Vector2(x / value.x, y / value.y); }

	void operator+=(double value) { x += value; y += value; }
	void operator-=(double value) { x -= value; y -= value; }
	void operator*=(double value) { x *= value; y *= value; }
	void operator/=(double value) { x /= value; y /= value; }

	void operator+=(const Vector2& value) { x += value.x; y += value.y; }
	void operator-=(const Vector2& value) { x -= value.x; y -= value.y; }
	void operator*=(const Vector2& value) { x *= value.x; y *= value.y; }
	void operator/=(const Vector2& value) { x /= value.x; y /= value.y; }

	void operator=(double value) { x = value; y = value; }
	void operator=(const Vector2& value) { x = value.x; y = value.y; }

	bool operator==(double value) { return x == value && y == value; }
	bool operator==(const Vector2& value) { return x == value.x && y == value.y; }

	bool operator!=(double value) { return x != value && y != value; }
	bool operator!=(const Vector2& value) { return x != value.x && y != value.y; }

	const Vector2 Half() { return Vector2(x / 2.0, y / 2.0); }

	void Normalize() { double norm = Norm(); if (norm > 0.0) { x /= norm; y /= norm; } }

	static double Dot(const Vector2& v1, const Vector2& v2) { return v1.x * v2.x + v1.y * v2.y; }

	void ZeroReset() { x = 0; y = 0; }

private:
	double Norm() { return sqrt(pow(x + y, 2)); }
};

//Vector2 operator+(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x + v2.x, v1.y + v2.y); }
//Vector2 operator-(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x - v2.x, v1.y + v2.y); }
//Vector2 operator*(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x * v2.x, v1.y * v2.y); }
//
//Vector2 operator*(const Vector2& value, double scaler) { return Vector2(value.x * scaler, value.y * scaler); }
//Vector2 operator*(double scaler, const Vector2& value) { return Vector2(value.x * scaler, value.y * scaler); }