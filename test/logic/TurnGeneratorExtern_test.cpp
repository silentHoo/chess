#include <gtest/gtest.h>
#include "logic/GameState.h"

/* TESTING the generated turns */
std::vector<Turn> turns_calc;
std::vector<Turn> turns_fine;



TEST(TurnGeneratorExtern, generateTurns_1) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Pawn), E2),
                                     PoF(Piece(White, Pawn), F2)}));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, E3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, E4));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), F2, F3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), F2, F4));

    EXPECT_EQ(turnVecCompare(turns_calc, turns_fine), true)
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_2) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), H1),
                                     PoF(Piece(White, Pawn), C5),
                                     PoF(Piece(White, Pawn), D6)}));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), H1, H2));
    turns_fine.push_back(Turn::move(Piece(White, King), H1, G2));
    turns_fine.push_back(Turn::move(Piece(White, King), H1, G1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), C5, C6));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), D6, D7));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}

TEST(TurnGeneratorExtern, generateTurns_EnPassant) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), H1),
                                     PoF(Piece(Black, King), A8),
                                     PoF(Piece(White, Pawn), D2),
                                     PoF(Piece(Black, Pawn), E4)}));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, Pawn), D2, D3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), D2, D4));
    EXPECT_TRUE(turnVecContains(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);

    gs.applyTurn(Turn::move(Piece(White, Pawn), D2, D4));
    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(Black, Pawn), E4, D3));
    turns_fine.push_back(Turn::move(Piece(Black, Pawn), E4, E3));
    EXPECT_TRUE(turnVecContains(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_Castle_1) {
    GameState gs(ChessBoard::fromFEN("k7/8/8/8/8/8/P6P/R3K2R w KQkq - 0 1"));
    EXPECT_TRUE(gs.getChessBoard().getShortCastleRights()[White]);
    EXPECT_TRUE(gs.getChessBoard().getLongCastleRights()[White]);
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::castle(Piece(White, King), E1, C1));
    turns_fine.push_back(Turn::castle(Piece(White, King), E1, G1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, Rook), A1, B1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), A1, C1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), A1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), H1, G1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), H1, F1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), A2, A3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), A2, A4));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), H2, H3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), H2, H4));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);

    gs.applyTurn(Turn::castle(Piece(White, King), E1, C1));
    EXPECT_FALSE(gs.getChessBoard().getShortCastleRights()[White]);
    EXPECT_FALSE(gs.getChessBoard().getLongCastleRights()[White]);

    // TODO: Not the same Score for gs and gs2 ???
    //GameState gs2(ChessBoard::fromFEN("8/8/8/8/8/8/P6P/2KR3R b kq - 0 1"));
    //EXPECT_EQ(gs2.getChessBoard(), gs.getChessBoard());
}
TEST(TurnGeneratorExtern, generateTurns_Castle_2) {
    GameState gs(ChessBoard::fromFEN("k7/8/8/8/8/8/7P/R3K2R w KQkq - 0 1"));
    EXPECT_TRUE(gs.getChessBoard().getShortCastleRights()[White]);
    EXPECT_TRUE(gs.getChessBoard().getLongCastleRights()[White]);

    gs.applyTurn(Turn::move(Piece(White, Rook), A1, B1));
    EXPECT_TRUE(gs.getChessBoard().getShortCastleRights()[White]);
    EXPECT_FALSE(gs.getChessBoard().getLongCastleRights()[White]);

    gs.applyTurn(Turn::pass(Black));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::castle(Piece(White, King), E1, G1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, C1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, A1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B2));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B3));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B4));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B5));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B6));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B7));
    turns_fine.push_back(Turn::move(Piece(White, Rook), B1, B8));
    turns_fine.push_back(Turn::move(Piece(White, Rook), H1, G1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), H1, F1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), H2, H3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), H2, H4));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_Castle_3) {
    GameState gs(ChessBoard::fromFEN("r1bqkb1r/1ppp1pp1/p1n1pn1p/8/2N5/4PN2/PPPPBPPP/R1BQK2R w KQkq - 2 6"));

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::castle(Piece(White, King), E1, G1));
    EXPECT_TRUE(turnVecContains(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_Castle_Check_1) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Rook), H1),
                                     PoF(Piece(Black, King), F8)}));
    gs.applyTurn(Turn::castle(Piece(White, King), E1, G1));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[Black]);
}
TEST(TurnGeneratorExtern, generateTurns_Castle_Check_2) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Rook), H1),
                                     PoF(Piece(White, Pawn), H2),
                                     PoF(Piece(Black, Queen), F6)}));
    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), H2, H3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), H2, H4));
    turns_fine.push_back(Turn::move(Piece(White, Rook), H1, G1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), H1, F1));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}

TEST(TurnGeneratorExtern, generateTurns_PromotionWhite) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(Black, Pawn), A3),
                                     PoF(Piece(White, Pawn), B8),
                                     PoF(Piece(White, Pawn), E8)}));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[White]);
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::promotionQueen (Piece(White, Pawn), B8));
    turns_fine.push_back(Turn::promotionBishop(Piece(White, Pawn), B8));
    turns_fine.push_back(Turn::promotionRook  (Piece(White, Pawn), B8));
    turns_fine.push_back(Turn::promotionKnight(Piece(White, Pawn), B8));
    turns_fine.push_back(Turn::promotionQueen (Piece(White, Pawn), E8));
    turns_fine.push_back(Turn::promotionBishop(Piece(White, Pawn), E8));
    turns_fine.push_back(Turn::promotionRook  (Piece(White, Pawn), E8));
    turns_fine.push_back(Turn::promotionKnight(Piece(White, Pawn), E8));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_PromotionBlack) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), E8),
                                     PoF(Piece(Black, Pawn), F1)}, Black));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(Black, King), E8, D8));
    turns_fine.push_back(Turn::move(Piece(Black, King), E8, D7));
    turns_fine.push_back(Turn::move(Piece(Black, King), E8, E7));
    turns_fine.push_back(Turn::move(Piece(Black, King), E8, F7));
    turns_fine.push_back(Turn::move(Piece(Black, King), E8, F8));
    turns_fine.push_back(Turn::promotionQueen(Piece(Black, Pawn), F1));
    turns_fine.push_back(Turn::promotionBishop(Piece(Black, Pawn), F1));
    turns_fine.push_back(Turn::promotionRook(Piece(Black, Pawn), F1));
    turns_fine.push_back(Turn::promotionKnight(Piece(Black, Pawn), F1));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_PromotionCheck) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), G8),
                                     PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Pawn), B8)}));
    gs.applyTurn(Turn::promotionRook(Piece(White, Pawn), B8));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[Black]) << gs;
    gs.applyTurn(Turn::move(Piece(Black, King), G8, G7));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[Black]) << gs;
}
TEST(TurnGeneratorExtern, generateTurns_PromotionCheckAndCheckmate) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Pawn), B8),
                                     PoF(Piece(White, Queen), E6),
                                     PoF(Piece(Black, King), D8)}));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[Black]) << gs;
    gs.applyTurn(Turn::promotionQueen(Piece(White, Pawn), B8));
    EXPECT_TRUE(gs.getChessBoard().getCheckmate()[Black]) << gs;
}

TEST(TurnGeneratorExtern, generateTurns_Check_1) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), G8),
                                     PoF(Piece(White, Pawn), F7)}, Black));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[Black]) << gs;
}
TEST(TurnGeneratorExtern, generateTurns_Check_2) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E2),
                                     PoF(Piece(White, Pawn), D3),
                                     PoF(Piece(Black, Queen), B5)}));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[White]);
}
TEST(TurnGeneratorExtern, generateTurns_setKingInCheck) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(Black, King), E8),
                                     PoF(Piece(Black, Queen), A5)}, Black));
    gs.applyTurn(Turn::move(Piece(Black, Queen), A5, E5));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}

TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_1) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(Black, Queen), F5)}));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));

    EXPECT_EQ(turnVecCompare(turns_calc, turns_fine), true)
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Pawn_1) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(Black, Pawn), C3)}));
    turns_calc = gs.getTurnList();

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));

    EXPECT_EQ(turnVecCompare(turns_calc, turns_fine), true)
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Pawn_2) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(Black, Pawn), E2)}));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Pawn_3) {
    GameState gs(ChessBoard::fromFEN("r1bqkbnr/pppppppp/8/8/8/N1Pn1N2/PP1PPPPP/R1BQKB1R w KQkq - 1 4"));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, D3));

    TurnGenerator tGen;
    BitBoard bbUnCheckFields = tGen.calcUnCheckFields(Black, gs.getChessBoard());

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc) << bitBoardToString(bbUnCheckFields);
}

TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Rook) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E2),
                                     PoF(Piece(Black, Rook), B2),
                                     PoF(Piece(Black, Rook), H1)}));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    // NOT: F2
    turns_fine.push_back(Turn::move(Piece(White, King), E2, D3));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, E3));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, F3));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Queen) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E2),
                                     PoF(Piece(Black, Queen), C4)}));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    // NOT: F1
    turns_fine.push_back(Turn::move(Piece(White, King), E2, E3));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, F3));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, F2));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, E1));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E2, D2));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}

TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Pawn) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Rook), F2),
                                     PoF(Piece(Black, Pawn), D2)}));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();

    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, Rook), F2, D2));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Knight) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Rook), F3),
                                     PoF(Piece(Black, Knight), D3)}));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();

    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), F3, D3));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}

TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_Rook_2) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Rook), C2),
                                     PoF(Piece(Black, Pawn), F2)}));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, E2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Rook), C2, F2));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_FilterCheckTurns_misc) {
    GameState gs(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Bishop), F1),
                                     PoF(Piece(White, Knight), G1),
                                     PoF(Piece(White, Rook), D2),
                                     PoF(Piece(Black, Queen), E4),
                                     PoF(Piece(Black, Pawn), G3)}));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[White]);

    turns_calc = gs.getTurnList();
    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Bishop), F1, E2));
    turns_fine.push_back(Turn::move(Piece(White, Knight), G1, E2));
    turns_fine.push_back(Turn::move(Piece(White, Rook), D2, E2));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine))
            << gs << turnVecToString(turns_calc);

    gs.applyTurn(Turn::move(Piece(White, Bishop), F1, E2));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[White]) << gs;
}



TEST(TurnGeneratorExtern, generateTurns_Stalemate_1) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), A8),
                                     PoF(Piece(White, King), B6),
                                     PoF(Piece(White, Knight), C6)}, Black));
    turns_calc = gs.getTurnList();
    EXPECT_TRUE(gs.getChessBoard().getStalemate())
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_Stalemate_2) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), A1),
                                     PoF(Piece(Black, Pawn), A2),
                                     PoF(Piece(White, Queen), B3)}, Black));
    turns_calc = gs.getTurnList();
    EXPECT_TRUE(gs.getChessBoard().getStalemate())
            << gs << turnVecToString(turns_calc);
}
TEST(TurnGeneratorExtern, generateTurns_Checkmate_1) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), A8),
                                     PoF(Piece(White, Rook), A5),
                                     PoF(Piece(White, Rook), B5)}, Black));
    EXPECT_TRUE(gs.getChessBoard().getKingInCheck()[Black]);
    EXPECT_TRUE(gs.getChessBoard().getCheckmate()[Black]);
}
TEST(TurnGeneratorExtern, generateTurns_Checkmate_2) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), H8),
                                     PoF(Piece(White, King), G6),
                                     PoF(Piece(White, Queen), B7)}));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[Black]) << gs;
    gs.applyTurn(Turn::move(Piece(White, Queen), B7, C8));
    EXPECT_TRUE(gs.getChessBoard().getCheckmate()[Black]) << gs;
}
TEST(TurnGeneratorExtern, generateTurns_Checkmate_3) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), H8),
                                     PoF(Piece(White, King), G6),
                                     PoF(Piece(White, Queen), B7)}));
    EXPECT_FALSE(gs.getChessBoard().getKingInCheck()[Black]) << gs;
    gs.applyTurn(Turn::move(Piece(White, Queen), B7, G7));
    EXPECT_TRUE(gs.getChessBoard().getCheckmate()[Black]) << gs;
}
TEST(TurnGeneratorExtern, generateTurns_FoolCheckmate) {
    GameState gs(ChessBoard::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));

    Turn turn = Turn::move(Piece(White, Pawn), F2, F3);
    turns_calc = gs.getTurnList();
    EXPECT_TRUE(turnVecContains(turns_calc, turn));
    gs.applyTurn(turn);

    turn = Turn::move(Piece(Black, Pawn), E7, E6);
    turns_calc = gs.getTurnList();
    EXPECT_TRUE(turnVecContains(turns_calc, turn));
    gs.applyTurn(turn);

    turn = Turn::move(Piece(White, Pawn), G2, G4);
    turns_calc = gs.getTurnList();
    EXPECT_TRUE(turnVecContains(turns_calc, turn));
    gs.applyTurn(turn);

    turn = Turn::move(Piece(Black, Queen), D8, H4);
    turns_calc = gs.getTurnList();
    EXPECT_TRUE(turnVecContains(turns_calc, turn));
    gs.applyTurn(turn);

    turns_calc = gs.getTurnList();
    EXPECT_TRUE(gs.getChessBoard().getCheckmate()[White])
            << gs << turnVecToString(turns_calc);
}




//TurnGenerator tGen;
//BitBoard bb = tGen.calcAllOppTurns(Black, gs.getChessBoard());
//<< bitBoardToString(bb);

/*
TEST(TurnGeneratorExtern, generateTurns_deathPosition) {
    GameState gs(generateChessBoard({PoF(Piece(Black, King), D8),
                                     PoF(Piece(White, Rook), D6)}, Black));
    // tote Stellung? Beispiele auf http://de.wikipedia.org/wiki/Tote_Stellung

    // 3rkbr1/p1Nn1pp1/3p3p/8/8/3PP3/PP3PPP/R1B3KR b - - 94 68 ???
}
*/