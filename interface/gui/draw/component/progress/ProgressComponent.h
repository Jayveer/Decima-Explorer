#pragma once
#include "../Component.h"

class ProgressComponent : public Component {
public:
	ProgressComponent();
	~ProgressComponent();

	void completed();
	void increment();
	bool isCompleted();
	void setValue(int32_t value);
	void setRange(int32_t maxRange);
	void setCustomIncrement(int increment);
	void create(HWND parent, Dimensions dimensions, Origin origin);

	uint32_t current = 0;
	uint32_t maxRange;
};