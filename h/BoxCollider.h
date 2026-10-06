#pragma once
#include	"Vector2.h"
#include	"Vector2Int.h"

class BoxCollider {
protected:
	virtual bool CheckHit(int posX, int posY, double sizeX, double sizeY) = 0;
	virtual bool CheckHit(Vector2Int pos, Vector2 size) = 0;
	//virtual bool CheckHit(const Box& other) = 0;
};