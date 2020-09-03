#pragma once
#include "../Component.h"

class MenuComponent : public Component {
public:
	MenuComponent();
	~MenuComponent();

	void create(HWND parent);
};