#include "Class.h"

void GameObject::SetPosition(IntVector2 value) {
	pos.Get(X) = value.Get(X);
	pos.y = value.y;
}

int GameObject::GetPosition(bool X_OR_Y) const { return X_OR_Y ? pos.x : pos.y; }

const IntVector2 GameObject::GetPosition() const { return pos; }

void GameObject::SetSize(IntVector2 value) {
	size.x = value.x;
	size.y = value.y;
}