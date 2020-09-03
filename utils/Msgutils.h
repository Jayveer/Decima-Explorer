#pragma once

class MessageHandler {
public:
	virtual void showError(const char* message) = 0;
	virtual void showMessage(const char* message) = 0;
	virtual void showWarning(const char* message) = 0;
};