#include <iostream>

#include "GuiObserver.h"
#include "misc/helper.h"
#include <thread>

#include "gui/states/GamePlay.h"

using namespace std;

GuiObserver::GuiObserver(ChessSetPtr chessSetPtr, GamePlay& gamePlayState)
	: m_chessSetPtr(chessSetPtr)
	, m_gamePlayState(gamePlayState) {
}

void GuiObserver::onGameStart(GameState state, GameConfiguration config) {
	m_gamePlayState.setState(state.getChessBoard().getBoard());
	m_gamePlayState.setCapturedPiecesList(state.getChessBoard().getCapturedPieces());
}

void GuiObserver::onTurnStart(PlayerColor who) {
	m_gamePlayState.switchToPlayerColor(who);
}

void GuiObserver::onTurnEnd(PlayerColor who, Turn turn, GameState newState) {
	m_gamePlayState.addTurn(who, turn);
	m_gamePlayState.setState(newState.getChessBoard().getBoard());
	m_gamePlayState.setCapturedPiecesList(newState.getChessBoard().getCapturedPieces());
}

void GuiObserver::onTurnTimeout(PlayerColor who, std::chrono::seconds timeout) {
	stringstream strs;
	strs << (who == PlayerColor::Black ? "Schwarz" : "Weiss") << " hat zu lange gebraucht.";

	m_gamePlayState.startShowText(strs.str());
}

void GuiObserver::onGameOver(GameState state, PlayerColor winner) {
	stringstream strs;
	strs << (winner == PlayerColor::Black ? "Schwarz" : "Weiss") << " hat gewonnen. Das Spiel ist zu Ende.";

	m_gamePlayState.startShowText(strs.str());
}