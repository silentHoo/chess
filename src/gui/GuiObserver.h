/*
    Copyright (c) 2013-2014, Patrick Hillert <silent@gmx.biz>

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <memory>

#include "logic/interface/AbstractGameObserver.h"
#include "gui/ChessSet.h"

class GamePlay;

/**
 * @brief Allows to observe relevant GameEvents inside the GameLogic.
 * Classes of this type can be registered with the GameLogic to be
 * notified of relevant game events.
 *
 * @note A Observer is only required to stay in a valid state for one game.
 * It is free to halt its operations after the end of the game.
 *
 * @warning None of the functions in the class must block.
 */
class GuiObserver : public AbstractGameObserver {
public:
    /**
     * @brief Creates a new observer object.
     * @param chessSetPtr A shared pointer to the ChessSet object.
     * @param gamePlayState A reference to the GamePlay state.
     */
    GuiObserver(ChessSetPtr chessSetPtr, GamePlay& gamePlayState);

    /**
     * @brief Called when the game starts.
     * @param state GameState on game start.
     * @param config Valid GameConfiguration for this game.
     */
    void onGameStart(GameState state, GameConfiguration config) override;

    /**
     * @brief Called if a player is asked to perform a turn.
     * @param who Color of the player doing the turn.
     */
    void onTurnStart(PlayerColor who) override;

    /**
     * @brief Called if a player ended its turn.
     * @param who Color of the player doing the turn.
     * @param turn Turn the player decided on.
     * @param newState State after the player performed the turn.
     */
    void onTurnEnd(PlayerColor who, Turn turn, GameState newState) override;

    /**
     * @brief Called if a players turn is aborted due to timeout.
     * @param who Color of the player who got interrupted.
     * @param timeout Length of the time limit that got violated.
     */
    void onTurnTimeout(PlayerColor who, std::chrono::seconds timeout) override;

    /**
     * @brief Called when a game started with onGameStart is over.
     * @param state State on game over.
     * @param winner Winner of the game.
     */
    void onGameOver(GameState state, PlayerColor winner) override;

private:
    //! Shared pointer to the ChessSet.
    ChessSetPtr m_chessSetPtr;

    //! Shared pointer to the GamePlay state.
    GamePlay& m_gamePlayState;
};

using GuiObserverPtr = std::shared_ptr<GuiObserver>; // Shared pointer for better garbage handling.

#endif // GAMEOBSERVER_H
