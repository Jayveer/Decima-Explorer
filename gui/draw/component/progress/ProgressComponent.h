#pragma once
#include "../Component.h"

class ProgressComponent : Component {
public:
	ProgressComponent();
	~ProgressComponent();

	void create(HWND parent, Dimensions dimensions, Origin origin);
	void setRange(int maxRange);
	void setIncrement();
	void increment();

};