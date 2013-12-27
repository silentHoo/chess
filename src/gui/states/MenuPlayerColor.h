#ifndef MENUPLAYERCOLOR_H
#define MENUPLAYERCOLOR_H

#include "gui/interface/AbstractState.h"
#include "gui/Menu2D.h"

class StateMachine;

class MenuPlayerColor : public AbstractState {
public:
	MenuPlayerColor();

	// interface methods
	void enter() override;
	AbstractState* run() override;
	void exit() override;

	// draw method
	void draw();

	// state methods
	void onColorWhite();
	void onColorBlack();
	void onMenuBack();

private:
	StateMachine& m_fsm;
	bool m_colorWhite;

	enum States {
		KEEP_CURRENT,

		GAME_PLAY,
		MENU_GAME_MODE
	};
	States m_nextState;

	// menu smart pointer handle
	Menu2DPtr m_menu;
};

#endif // MENUPLAYERCOLOR_H