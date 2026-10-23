#pragma once
#include	"Vector2Int.h"
#include	"Vector2.h"
#include	"GameObject.h"

class IMovable {
public:
	void Forward(Vector2Int main, Vector2Int add) { main += add; }
	void Forward(Vector2Int main, Vector2 add) { main += Vector2Int((int)add.x, (int)add.y); }
};

class IChangable {
public:
	void Change(Vector2Int main, Vector2Int change) { main = change; }
	void Change(Vector2Int main, Vector2 change) { main = Vector2Int((int)change.x, (int)change.y); }
};