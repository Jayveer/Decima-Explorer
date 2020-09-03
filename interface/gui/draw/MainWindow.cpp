#include "MainWindow.h"

MainWindow::MainWindow() : window(this) {

}

MainWindow::~MainWindow() {

}

void MainWindow::run(std::string programName, std::string version) {
	std::string name = programName + " v" + version;
	SetWindowText(getHandle(), name.c_str());
	window.run();
}

HWND MainWindow::getHandle() {
	return window.getHandle();
}

void MainWindow::create(HINSTANCE hInst, WindowCaller* caller, const char* title, HICON icon, HICON iconSm, uint32_t bgColour) {
	window.setCaller(caller);
	window.create(hInst, "mainWindow", title, icon, iconSm, bgColour);
}

ComponentType determineType(HWND hwnd) {
	Component* component = (Component*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	return component ? component->getType() : INVALID;
}

LRESULT MainWindow::ProcedureWrapper(HWND inHwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CREATE: {
		if (determineType(inHwnd) == WINDOW) {
			WindowComponent* window = (WindowComponent*)GetWindowLongPtr(inHwnd, GWLP_USERDATA);
			if (window) window->created();
		}
	} break;
	case WM_CTLCOLORSTATIC: {
		HWND childHwnd = (HWND)lParam;
		if (determineType(childHwnd) == VIEW) {
			ViewComponent* view = (ViewComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (view) return (INT_PTR)view->drawing(HDC(wParam));
		}

		if (determineType(childHwnd) == TEXTFIELD) {
			TextfieldComponent* textfield = (TextfieldComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (textfield) return (INT_PTR)textfield->drawing(HDC(wParam));
		}

	} break;
	case WM_CTLCOLORBTN: {
		HWND childHwnd = (HWND)lParam;
		if (determineType(childHwnd) == BUTTON) {
			ButtonComponent* button = (ButtonComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (button) return (INT_PTR)button->drawing(HDC(wParam));
		}
	} break;
	case WM_CTLCOLOREDIT: {
		HWND childHwnd = (HWND)lParam;
		if (determineType(childHwnd) == TEXTFIELD) {
			TextfieldComponent* textfield = (TextfieldComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (textfield) return (INT_PTR)textfield->drawing(HDC(wParam));
		}
	} break;
	case WM_CONTEXTMENU: {
		HWND childHwnd = (HWND)wParam;
		if (determineType(childHwnd) == LISTVIEW) {
			ListComponent* listview = (ListComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (listview) listview->rightClicked(LOWORD(lParam), HIWORD(lParam));
		}

		if (determineType(childHwnd) == WINDOW) {
			WindowComponent* window = (WindowComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (window) window->rightClicked(LOWORD(lParam), HIWORD(lParam));
		}
	} break;
	case WM_COMMAND: {
		HWND childHwnd = (HWND)lParam;
		if (determineType(childHwnd) == BUTTON) {
			ButtonComponent* button = (ButtonComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (button) button->clicked();
		}
		if (determineType(childHwnd) == TEXTFIELD) {
			TextfieldComponent* textfield = (TextfieldComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (textfield && HIWORD(wParam) == EN_CHANGE) textfield->changed();
		}
		if (determineType(childHwnd) == VIEW) {
			ViewComponent* view = (ViewComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (view) view->clicked();
		}
	} break;
	case WM_NOTIFY: {
		NMHDR* nm = (NMHDR*)lParam;
		HWND childHwnd = nm->hwndFrom;
		if (determineType(childHwnd) == LISTVIEW) {
			ListComponent* listview = (ListComponent*)GetWindowLongPtr(childHwnd, GWLP_USERDATA);
			if (listview && nm->code == LVN_ENDSCROLL) listview->scrolled();
			if (listview && nm->code == LVN_ITEMCHANGED) listview->selected();
			if (listview && nm->code == LVN_GETDISPINFO) listview->populating((NMLVDISPINFO*)lParam); 
			if (listview && nm->code == LVN_COLUMNCLICK) listview->columnClicked(((NMLISTVIEW*)lParam)->iSubItem);
			if (listview && nm->code == LVN_KEYDOWN) listview->keyPressed(((NMLVKEYDOWN*)lParam));
		}
	}break;
	case WM_CLOSE: {
		DestroyWindow(inHwnd);
	} break;
	case WM_DESTROY: {
		PostQuitMessage(0);
	} break;
	default:
		return DefWindowProc(inHwnd, message, wParam, lParam);
	}
	return 0;
}