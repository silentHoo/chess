#include <gtest/gtest.h>
#include "logic/TurnGenerator.h"

TurnGenerator tGen;



BitBoard bb_calc;
BitBoard bb_fine;
/* TESTING mask and clear functions */
TEST(TurnGenerator, maskRank_One) {
    bb_calc = tGen.maskRank(One);
    bb_fine = generateBitBoard(A1, B1, C1, D1, E1, F1, G1, H1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, maskRank_Four) {
    bb_calc = tGen.maskRank(Four);
    bb_fine = generateBitBoard(A4, B4, C4, D4, E4, F4, G4, H4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, maskRank_Six) {
    bb_calc = tGen.maskRank(Six);
    bb_fine = generateBitBoard(A6, B6, C6, D6, E6, F6, G6, H6, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}


TEST(TurnGenerator, clearRank_One) {
    bb_calc = tGen.clearRank(One);
    bb_fine = ULLONG_MAX - generateBitBoard(A1, B1, C1, D1, E1, F1, G1, H1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, clearRank_Four) {
    bb_calc = tGen.clearRank(Four);
    bb_fine = ULLONG_MAX - generateBitBoard(A4, B4, C4, D4, E4, F4, G4, H4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, maskFile_A) {
    bb_calc = tGen.maskFile(A);
    bb_fine = generateBitBoard(A1, A2, A3, A4, A5, A6, A7, A8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, maskFile_D) {
    bb_calc = tGen.maskFile(D);
    bb_fine = generateBitBoard(D1, D2, D3, D4, D5, D6, D7, D8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, clearFile_A) {
    bb_calc = tGen.clearFile(A);
    bb_fine = ULLONG_MAX - generateBitBoard(A1, A2, A3, A4, A5, A6, A7, A8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, clearFile_D) {
    bb_calc = tGen.clearFile(D);
    bb_fine = ULLONG_MAX - generateBitBoard(D1, D2, D3, D4, D5, D6, D7, D8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
/* TESTING getBitsX functions */
TEST(TurnGenerator, getBitsE_1) {
    bb_calc = tGen.getBitsE(BB_SET(D4));
    bb_fine = generateBitBoard(E4, F4, G4, H4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsE_2) {
    bb_calc = tGen.getBitsE(BB_SET(A5));
    bb_fine = generateBitBoard(B5, C5, D5, E5, F5, G5, H5, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsE_3) {
    bb_calc = tGen.getBitsE(BB_SET(H5));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsW_1) {
    bb_calc = tGen.getBitsW(BB_SET(D4));
    bb_fine = generateBitBoard(A4, B4, C4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsW_2) {
    bb_calc = tGen.getBitsW(BB_SET(H5));
    bb_fine = generateBitBoard(A5, B5, C5, D5, E5, F5, G5, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsW_3) {
    bb_calc = tGen.getBitsW(BB_SET(A5));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsN_1) {
    bb_calc = tGen.getBitsN(BB_SET(D4));
    bb_fine = generateBitBoard(D5, D6, D7, D8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsN_2) {
    bb_calc = tGen.getBitsN(BB_SET(D1));
    bb_fine = generateBitBoard(D2, D3, D4, D5, D6, D7, D8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsN_3) {
    bb_calc = tGen.getBitsN(BB_SET(D8));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsS_1) {
    bb_calc = tGen.getBitsS(BB_SET(D4));
    bb_fine = generateBitBoard(D3, D2, D1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsS_2) {
    bb_calc = tGen.getBitsS(BB_SET(D8));
    bb_fine = generateBitBoard(D7, D6, D5, D4, D3, D2, D1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsS_3) {
    bb_calc = tGen.getBitsS(BB_SET(D1));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsS_4) {
    bb_calc = tGen.getBitsS(BB_SET(A1));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
/* TESTING getBitsXY functions */
TEST(TurnGenerator, getBitsNE_1) {
    bb_calc = tGen.getBitsNE(BB_SET(A1));
    bb_fine = generateBitBoard(B2, C3, D4, E5, F6, G7, H8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNE_2) {
    bb_calc = tGen.getBitsNE(BB_SET(A4));
    bb_fine = generateBitBoard(B5, C6, D7, E8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNE_3) {
    bb_calc = tGen.getBitsNE(BB_SET(E1));
    bb_fine = generateBitBoard(F2, G3, H4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNE_4) {
    bb_calc = tGen.getBitsNE(BB_SET(F3));
    bb_fine = generateBitBoard(G4, H5, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNE_5) {
    bb_calc = tGen.getBitsNE(BB_SET(A8));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNW_1) {
    bb_calc = tGen.getBitsNW(BB_SET(H1));
    bb_fine = generateBitBoard(G2, F3, E4, D5, C6, B7, A8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNW_2) {
    bb_calc = tGen.getBitsNW(BB_SET(D1));
    bb_fine = generateBitBoard(C2, B3, A4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNW_3) {
    bb_calc = tGen.getBitsNW(BB_SET(G5));
    bb_fine = generateBitBoard(F6, E7, D8, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsNW_4) {
    bb_calc = tGen.getBitsNW(BB_SET(C8));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSE_1) {
    bb_calc = tGen.getBitsSE(BB_SET(A8));
    bb_fine = generateBitBoard(B7, C6, D5, E4, F3, G2, H1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSE_2) {
    bb_calc = tGen.getBitsSE(BB_SET(E8));
    bb_fine = generateBitBoard(F7, G6, H5, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSE_3) {
    bb_calc = tGen.getBitsSE(BB_SET(A4));
    bb_fine = generateBitBoard(B3, C2, D1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSE_4) {
    bb_calc = tGen.getBitsSE(BB_SET(G3));
    bb_fine = generateBitBoard(H2, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSE_5) {
    bb_calc = tGen.getBitsSE(BB_SET(A1));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSW_1) {
    bb_calc = tGen.getBitsSW(BB_SET(H8));
    bb_fine = generateBitBoard(G7, F6, E5, D4, C3, B2, A1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSW_2) {
    bb_calc = tGen.getBitsSW(BB_SET(D8));
    bb_fine = generateBitBoard(C7, B6, A5, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSW_3) {
    bb_calc = tGen.getBitsSW(BB_SET(H3));
    bb_fine = generateBitBoard(G2, F1, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, getBitsSW_4) {
    bb_calc = tGen.getBitsSW(BB_SET(A1));
    bb_fine = 0;
    EXPECT_EQ(bb_calc, bb_fine);
}



/* TESTING turn generation */
BitBoard bbKing;
BitBoard bbKnights;
BitBoard bbPawns;
BitBoard bbRooks;
BitBoard bbBishops;
BitBoard bbQueens;
BitBoard bbOwnPieces;
BitBoard bbOppPieces;

BitBoard bbTurns_calc;
BitBoard bbTurns_fine;

/* TESTING calcKingTurns */
TEST(TurnGenerator, calcKingTurns_A1) {
    bbKing = BB_SET(A1);
    bbTurns_calc = tGen.calcKingTurns(bbKing, 0, true, true);
    bbTurns_fine = generateBitBoard(B1, B2, A2, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
TEST(TurnGenerator, calcKingTurns_H1) {
    bbKing = BB_SET(H1);
    bbTurns_calc = tGen.calcKingTurns(bbKing, 0, true, true);
    bbTurns_fine = generateBitBoard(G1, G2, H2, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
TEST(TurnGenerator, calcKingTurns_A8) {
    bbKing = BB_SET(A8);
    bbTurns_calc = tGen.calcKingTurns(bbKing, 0, true, true);
    bbTurns_fine = generateBitBoard(B8, B7, A7, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
TEST(TurnGenerator, calcKingTurns_H8) {
    bbKing = BB_SET(H8);
    bbTurns_calc = tGen.calcKingTurns(bbKing, 0, true, true);
    bbTurns_fine = generateBitBoard(G8, G7, H7, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
TEST(TurnGenerator, calcKingTurns_C3) {
    bbKing = BB_SET(C3);
    bbTurns_calc = tGen.calcKingTurns(bbKing, 0, true, true);
    bbTurns_fine = generateBitBoard(D4, C4, B4, D3, B3, D2, C2, B2, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
TEST(TurnGenerator, calcKingTurns_F4) {
    bbKing = BB_SET(F4);
    bbOwnPieces = generateBitBoard(C5, B3, E5, F5, F3, ERR);
    bbTurns_calc = tGen.calcKingTurns(bbKing, bbOwnPieces, true, true);
    bbTurns_fine = generateBitBoard(G5, G4, G3, E3, E4, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
// TODO: test check and checkmate



/* TESTING calcKnightTurns */
TEST(TurnGenerator, calcKnightTurns_Start) {
    bbKnights = generateBitBoard(B1, G1, ERR);
    bbOwnPieces = tGen.maskRank(Two);
    bbTurns_calc = tGen.calcKnightTurns(bbKnights, bbOwnPieces);
    bbTurns_fine = generateBitBoard(C3, A3, F3, H3, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}
TEST(TurnGenerator, calcKnightTurns_All) {
    bbKnights = BB_SET(D4);
    bbTurns_calc = tGen.calcKnightTurns(bbKnights, 0);
    bbTurns_fine = generateBitBoard(E6, F5, F3, E2, C2, B3, B5, C6, ERR);
    EXPECT_EQ(bbTurns_calc, bbTurns_fine);
}



/* TESTING calcPawnTurns */
TEST(TurnGenerator, calcPawnTurns_StartWhite) {
    bbPawns = generateBitBoard(A2, B2, C2, D2, E2, F2, G2, H2, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, 0, bbPawns, White);
    bb_fine = tGen.maskRank(Three) + tGen.maskRank(Four);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_StartBlack) {
    bbPawns = generateBitBoard(A7, B7, C7, D7, E7, F7, G7, H7, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, 0, bbPawns, Black);
    bb_fine = tGen.maskRank(Six) + tGen.maskRank(Five);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_AttackWhite_1) {
    bbPawns = BB_SET(A4);
    bbOppPieces = generateBitBoard(A5, B5, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, White);
    bb_fine = BB_SET(B5);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_AttackBlack_1) {
    bbPawns = BB_SET(A7);
    bbOppPieces = BB_SET(B6);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, Black);
    bb_fine = generateBitBoard(A6, A5, B6, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_AttackWhite_2) {
    bbPawns = BB_SET(H2);
    bbOppPieces = BB_SET(G3);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, White);
    bb_fine = generateBitBoard(G3, H3, H4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_AttackBlack_2) {
    bbPawns = BB_SET(H5);
    bbOppPieces = generateBitBoard(H4, G4, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, Black);
    bb_fine = BB_SET(G4);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_AttackWhite_3) {
    bbPawns = BB_SET(D2);
    bbOppPieces = generateBitBoard(C3, E3, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, White);
    bb_fine = generateBitBoard(C3, E3, D3, D4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
TEST(TurnGenerator, calcPawnTurns_AttackBlack_3) {
    bbPawns = BB_SET(C5);
    bbOppPieces = BB_SET(D4);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, Black);
    bb_fine = generateBitBoard(D4, C4, ERR);
    EXPECT_EQ(bb_calc, bb_fine);
}
// TODO: test en passant



/* TESTING calcQueenTurns */
TEST(TurnGenerator, calcQueenTurns_allMoves) {
    bbQueens = BB_SET(D4);
    bb_calc = tGen.calcQueenTurns(bbQueens, 0, bbQueens);
    bb_fine = generateBitBoard(E4, F4, G4, H4,   /* E */
                               C4, B4, A4,       /* W */
                               D5, D6, D7, D8,   /* N */
                               D3, D2, D1,       /* S */
                               E5, F6, G7, H8,   /* NE */
                               C5, B6, A7,       /* NW */
                               E3, F2, G1,       /* SE */
                               C3, B2, A1, ERR); /* SW */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcQueenTurns_stop) {
    bbQueens = BB_SET(D4);
    bbOppPieces = BB_SET(E4);
    bbOwnPieces = BB_SET(B2);
    bb_calc = tGen.calcQueenTurns(bbQueens, bbOppPieces,
                                  bbQueens | bbOwnPieces | bbOppPieces);
    bb_fine = generateBitBoard(E4,               /* E */
                               C4, B4, A4,       /* W */
                               D5, D6, D7, D8,   /* N */
                               D3, D2, D1,       /* S */
                               E5, F6, G7, H8,   /* NE */
                               C5, B6, A7,       /* NW */
                               E3, F2, G1,       /* SE */
                               C3, ERR);         /* SW */
    EXPECT_EQ(bb_fine, bb_calc);

    //LOG(trace) << bitBoardToString(bb_calc);
    //LOG(trace) << bitBoardToString(bb_fine);
}



/* TESTING calcBishopTurns */
TEST(TurnGenerator, calcBishopTurns_allMoves) {
    bbBishops = BB_SET(C3);
    bbOppPieces = 0;
    bb_calc = tGen.calcBishopTurns(bbBishops, bbOppPieces, bbBishops | bbOppPieces);
    bb_fine = generateBitBoard(D4, E5, F6, G7, H8, /* NE */
                               B4, A5,             /* NW */
                               D2, E1,             /* SE */
                               B2, A1, ERR);       /* SW */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcBishopTurns_stopOwnPieces) {
    bbBishops = BB_SET(D5);
    bbOwnPieces = generateBitBoard(E6, A8, G2, B3, ERR);
    bb_calc = tGen.calcBishopTurns(bbBishops, 0, bbBishops | bbOwnPieces);
    bb_fine = generateBitBoard(          /* NE */
                               C6, B7,   /* NW */
                               E4, F3,   /* SE */
                               C4, ERR); /* SW */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcBishopTurns_stopOppPieces) {
    bbBishops = BB_SET(F2);
    bbOppPieces = generateBitBoard(H4, C5, ERR);
    bb_calc = tGen.calcBishopTurns(bbBishops, bbOppPieces, bbBishops | bbOppPieces);
    bb_fine = generateBitBoard(G3, H4,     /* NE */
                               E3, D4, C5, /* NW */
                               G1,         /* SE */
                               E1, ERR);   /* SW */
    EXPECT_EQ(bb_fine, bb_calc);
}




/* TESTING calcRookTurns */
TEST(TurnGenerator, calcRookTurns_allMoves) {
    bbRooks = BB_SET(C3);
    bbOppPieces = 0;
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces, bbRooks | bbOppPieces);
    bb_fine = generateBitBoard(D3, E3, F3, G3, H3, /* right */
                               A3, B3,             /* left  */
                               C4, C5, C6, C7, C8, /* up    */
                               C2, C1, ERR);       /* down */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_stopOwnPieces) {
    bbRooks = BB_SET(E4);
    bbOwnPieces = generateBitBoard(B4, E5, E2, G4, ERR);
    bb_calc = tGen.calcRookTurns(bbRooks, 0, bbRooks | bbOwnPieces);
    bb_fine = generateBitBoard(F4,           /* right */
                               D4, C4,       /* left  */
                                             /* up    */
                               E3, ERR);     /* down */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_stopOppPieces) {
    bbRooks = BB_SET(C5);
    bbOppPieces = generateBitBoard(G5, B5, C8, C3, ERR);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces);
    bb_fine = generateBitBoard(D5, E5, F5, G5, /* right */
                               B5,             /* left  */
                               C6, C7, C8,     /* up    */
                               C4, C3, ERR);   /* down */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_misc_1) {
    bbRooks = BB_SET(A1);
    bbOppPieces = BB_SET(A8);
    bbOwnPieces = BB_SET(C1);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces | bbOwnPieces);
    bb_fine = generateBitBoard(B1,                         /* right */
                                                           /* left  */
                               A2, A3, A4, A5, A6, A7, A8, /* up    */
                               ERR);                       /* down */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_misc_2) {
    bbRooks = BB_SET(G5);
    bbOppPieces = BB_SET(C5);
    bbOwnPieces = BB_SET(H5);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces | bbOwnPieces);
    bb_fine = generateBitBoard(                      /* right */
                               F5, E5, D5, C5,       /* left  */
                               G6, G7, G8,           /* up    */
                               G4, G3, G2, G1, ERR); /* down */
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_misc_3) {
    bbRooks = BB_SET(A1);
    bbOppPieces = generateBitBoard(A7, A8 ,ERR);
    bbOwnPieces = generateBitBoard(A2, B1 ,ERR);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces | bbOwnPieces);
    bb_fine = 0;
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_misc_4) {
    bbRooks = BB_SET(H8);
    bbOppPieces = generateBitBoard(H2, H1 ,ERR);
    bbOwnPieces = generateBitBoard(H7, G8 ,ERR);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces | bbOwnPieces);
    bb_fine = 0;
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_misc_5) {
    bbRooks = BB_SET(H1);
    bbOppPieces = generateBitBoard(H7, H8 ,ERR);
    bbOwnPieces = generateBitBoard(H2, G1 ,ERR);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces | bbOwnPieces);
    bb_fine = 0;
    EXPECT_EQ(bb_fine, bb_calc);
}
TEST(TurnGenerator, calcRookTurns_misc_6) {
    bbRooks = BB_SET(A8);
    bbOppPieces = generateBitBoard(A1, A2 ,ERR);
    bbOwnPieces = generateBitBoard(A7, B8 ,ERR);
    bb_calc = tGen.calcRookTurns(bbRooks, bbOppPieces,
                                 bbRooks | bbOppPieces | bbOwnPieces);
    bb_fine = 0;
    EXPECT_EQ(bb_fine, bb_calc);
}


/*
LOG(trace) << bitBoardToString(bb_calc);
LOG(trace) << bitBoardToString(bb_fine);
*/







/* TESTING the generated turns */
std::vector<Turn> turns_calc;
std::vector<Turn> turns_fine;

TEST(TurnGenerator, generateTurns_1) {
    ChessBoard cb(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Pawn), E2),
                                     PoF(Piece(Black, Pawn), F2)}));
    turns_calc = tGen.generateTurns(White, cb);

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, E3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, E4));

    // TODO: FALSCH! Koenig steht im Schach und daher sind die
    // gueltigen Turns nur:
    //turns_fine.push_back(Turn::move(Piece(White, King), E1, F2));
    //turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    //turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    //turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));

    EXPECT_EQ(turnVecCompare(turns_calc, turns_fine), true);
}
TEST(TurnGenerator, generateTurns_2) {
    ChessBoard cb(generateChessBoard({PoF(Piece(White, King), E1),
                                     PoF(Piece(White, Pawn), E2),
                                     PoF(Piece(White, Pawn), F2)}));
    turns_calc = tGen.generateTurns(White, cb);

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D2));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, F1));
    turns_fine.push_back(Turn::move(Piece(White, King), E1, D1));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, E3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), E2, E4));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), F2, F3));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), F2, F4));

    EXPECT_EQ(turnVecCompare(turns_calc, turns_fine), true);


    //LOG(trace) << cb;
    //LOG(trace) << turnVecToString(turns_calc);
}


TEST(TurnGenerator, generateTurns_3) {
    ChessBoard cb(generateChessBoard({PoF(Piece(White, Pawn), C5),
                                     PoF(Piece(White, Pawn), D6)}));
    turns_calc = tGen.generateTurns(White, cb);

    turns_fine.clear();
    turns_fine.push_back(Turn::move(Piece(White, Pawn), C5, C6));
    turns_fine.push_back(Turn::move(Piece(White, Pawn), D6, D7));

    EXPECT_TRUE(turnVecCompare(turns_calc, turns_fine));
}


/*
TEST(TurnGenerator, calcPawnTurns_AttackWhite_5) {
    bbPawns = generateBitBoard(F4, G5, ERR);
    bbOppPieces = 0; //generateBitBoard(D6, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, White);
    bb_fine = generateBitBoard(F5, G6, ERR);
    EXPECT_EQ(bb_calc, bb_fine);

    LOG(trace) << bitBoardToString(bb_calc);
    LOG(trace) << bitBoardToString(bb_fine);
}

TEST(TurnGenerator, calcPawnTurns_AttackWhite_6) {
    bbPawns = generateBitBoard(F4, ERR);
    bbOppPieces = generateBitBoard(G5, ERR);
    bb_calc = tGen.calcPawnTurns(bbPawns, bbOppPieces,
                                 bbPawns | bbOppPieces, White);
    bb_fine = generateBitBoard(F5, G5, ERR);
    EXPECT_EQ(bb_calc, bb_fine);

    LOG(trace) << bitBoardToString(bb_calc);
    LOG(trace) << bitBoardToString(bb_fine);
}
*/

/*
LOG(trace) << cb;
LOG(trace) << turnVecToString(turns_calc);
*/
