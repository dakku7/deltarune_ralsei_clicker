#pragma once
#include "Entity.h"

enum class ClickType {
	Default,
	AddClick
};

class Clickable : public Entity {
private:
	ClickType actionType = ClickType::Default;

public:

	Clickable() {

	}
	Clickable(ClickType action)
		: actionType(action)
	{

	}
	virtual bool contains(sf::Vector2f point) const = 0;
	virtual void clicked() = 0;
	virtual void setHovered(bool expr) = 0;

	ClickType getClickType() {
		return actionType;
	}
};