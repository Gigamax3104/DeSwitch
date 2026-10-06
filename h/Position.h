#pragma once
#include	"Vector2Int.h"
#include	"GameObject.h"

class IMovable {
protected:
	virtual void Forward(Vector2Int pos) = 0;
	virtual void Forward(Vector2 pos) = 0;

	virtual void Back(Vector2Int pos) = 0;
	virtual void Back(Vector2 pos) = 0;
};

class IChangable {
protected:
	virtual void Change(Vector2Int pos) = 0;
	virtual void Change(Vector2 pos) = 0;
};