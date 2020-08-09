#pragma once
#include "../Component.h"

class ProgressComponent : public Component {
public:
	ProgressComponent();
	~ProgressComponent();

	void create(HWND parent, Dimensions dimensions, Origin origin);
	void setRange(int32_t maxRange);
	void setIncrement();
	void increment();

};