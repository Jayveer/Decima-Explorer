#include "ProgressComponent.h"

ProgressComponent::ProgressComponent() {

}

ProgressComponent::~ProgressComponent() {

}

void ProgressComponent::create(HWND parent, Dimensions dimensions, Origin origin) {
    DWORD style = WS_CHILD | WS_VISIBLE;
    HWND hwnd = CreateWindow(PROGRESS_CLASS, "Loading file", style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
    setHandle(hwnd);
}

void ProgressComponent::setRange(int32_t maxRange) {
    this->maxRange = maxRange;
    SendMessage(getHandle(), PBM_SETRANGE32, 0, maxRange);
    SendMessage(getHandle(), PBM_SETSTEP, (WPARAM)1, 0);
}

void ProgressComponent::setCustomIncrement(int increment) {
    SendMessage(getHandle(), PBM_SETSTEP, (WPARAM)increment, 0);
}

void ProgressComponent::increment() {
    this->current++;
    SendMessage(getHandle(), PBM_STEPIT, 0, 0);
}

void ProgressComponent::setValue(int32_t value) {
    this->current = value;
    SendMessage(getHandle(), PBM_SETPOS, (WPARAM)value, 0);
}

bool ProgressComponent::isCompleted() {
    return current >= maxRange;
}

void ProgressComponent::completed() {

}