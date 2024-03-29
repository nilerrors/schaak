//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "Logging.h"
#include "consts.h"

#include "guicode/fileIO.h"
#include "guicode/message.h"

#include <QElapsedTimer>
#include <QEventLoop>
#include <QCoreApplication>


// Constructor
SchaakGUI::SchaakGUI() : ChessWindow(nullptr) {
    update();

    QMessageBox box;
    box.setText("Wilt u tegen AI spelen?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    int ret = box.exec();

    g.setAI_game(false);
    if (ret == QMessageBox::Yes) {
        g.setAI_game(true);
    }
}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    if (g.getGameEnded()) return;

    clearBoard();
    for (int rij = 0; rij < ROW_SIZE; rij++) {
        for (int kolom = 0; kolom < COL_SIZE; kolom++) {
            SchaakStuk* stuk = g.getPiece(rij, kolom);
            if (stuk != nullptr) setItem(rij, kolom, stuk);
        }
    }

    // boodschap als het eindigt of als gelijkspel
    if (g.schaakmat(zw::wit)) {
        g.endGame();
        message("Schaakmat! Zwart heeft gewonnen.");
        removeAllMarking();
        return;
    } else if (g.schaakmat(zw::zwart)) {
        g.endGame();
        message("Schaakmat! Wit heeft gewonnen.");
        removeAllMarking();
        return;
    } else if (g.pat(zw::wit) || g.pat(zw::zwart)) {
        g.endGame();
        message("Pat! Gelijkspel.");
        removeAllMarking();
        return;
    }
    if ((g.isAI_game() && g.getTurn() != zw::zwart) || !g.isAI_game()) {
        removeAllMarking();
        if (g.movePositionUnset()) {
            removeAllPieceThreats();
            if (displayThreats()) {
                // kleurt alle bedreigde schaakstukken
                // van beide kanten
                for (const auto &zet : g.threats()) {
                    setPieceThreat(zet.first, zet.second, true);
                }
            }
        } else {
            SchaakStuk* moveStuk = g.getPiece(g.getMovePosition().first,
                                              g.getMovePosition().second);

            setTileSelect(g.getMovePosition().first,g.getMovePosition().second, true);
            if (displayMoves()) {
                for (const auto &zet : moveStuk->geldige_zetten(g)) {
                    setTileFocus(zet.first, zet.second, true);
                }
            }
            if (displayKills()) {
                for (const auto &zet : g.kills(moveStuk)) {
                    setTileThreat(zet.first, zet.second, true);
                }
            }
        }
    }

    // het gedeelte waar de AI speelt.
    if (g.isAI_game() && g.getTurn() == zw::zwart) {
        removeAllMarking();

        // credit to Kartik Sharma: https://stackoverflow.com/a/11487434
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        QElapsedTimer timer;
        timer.start();
        while (true) {
            if (timer.elapsed() > AI_PAUSE) {
                g.AI_move();
                g.clearMovePosition();
                g.changeTurn();
                update();
                break;
            }
        }
    }
}

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    if (g.getGameEnded()) return;

    SchaakStuk* stuk = g.getPiece(r, k);
    if (g.movePositionUnset()) {
        if (stuk == nullptr) return;
        if (stuk->getKleur() != g.getTurn()) {
            message("Het is de beurt van " + QString(g.getTurn() == zw::wit ? "wit" : "zwart") + ".");
            return;
        }
    }

    logClickedPosition(r, k, stuk != nullptr ? stuk->piece() : Piece{Piece::None, Piece::Color::White});

    if (g.movePositionUnset()) {
        g.setMovePosition(r, k);
    } else {
        SchaakStuk* moveStuk = g.getPiece(g.getMovePosition().first,
                                          g.getMovePosition().second);

        if (r == moveStuk->getPositie().first && k == moveStuk->getPositie().second) {
            g.clearMovePosition();
        } else if (stuk != nullptr && stuk->getKleur() == moveStuk->getKleur()) {
            message("Deze zet is ongeldig.");
        } else {
            bool geldigeMove = false;
            Positions geldigeZetten = moveStuk->geldige_zetten(g);
            for (const auto &zet : geldigeZetten) {
                if (r == zet.first && k == zet.second) {
                    logBeweegStuk(r, k, moveStuk->piece());

                    geldigeMove = true;
                    g.move(moveStuk, zet);
                    g.clearMovePosition();
                    g.changeTurn();
                    break;
                }
            }
            if (!geldigeMove) {
                message("Deze zet is ongeldig.");
            }
        }
    }

    update();
}

void SchaakGUI::newGame() {
    QMessageBox box;
    box.setText("Wilt u tegen AI spelen?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    int ret = box.exec();

    g.setAI_game(false);
    if (ret == QMessageBox::Yes) {
        g.setAI_game(true);
    }

    g.clearMoves();
    g.clearMovePosition();
    removeAllMarking();
    g.setStartBord();
    if (g.getTurn() != zw::wit) {
        g.changeTurn();
    }
    update();
}


/// Save en open methods door het bord te bewaren
//void SchaakGUI::save() {
//    QFile file;
//    if (openFileToWrite(file)) {
//        QDataStream out(&file);
//
//        out << (g.getTurn() == zw::wit ? QString("TW") : QString("TB"));
//
//        for (int r = 0; r < ROW_SIZE; r++) {
//            for (int k = 0; k < COL_SIZE; k++) {
//                SchaakStuk* piece = g.getPiece(r, k);
//                if (piece == nullptr) {
//                    out << QString(".");
//                    continue;
//                }
//
//                switch (piece->piece().type()) {
//                    case Piece::Pawn:
//                        out << QString(piece->getKleur() == zw::wit ? "Pw" : "Pb");
//                        break;
//                    case Piece::Rook:
//                        out << QString(piece->getKleur() == zw::wit ? "Rw" : "Rb");
//                        break;
//                    case Piece::King:
//                        out << QString(piece->getKleur() == zw::wit ? "Hw" : "Hb");
//                        break;
//                    case Piece::Queen:
//                        out << QString(piece->getKleur() == zw::wit ? "Qw" : "Qb");
//                        break;
//                    case Piece::Bishop:
//                        out << QString(piece->getKleur() == zw::wit ? "Bw" : "Bb");
//                        break;
//                    case Piece::Knight:
//                        out << QString(piece->getKleur() == zw::wit ? "Kw" : "Kb");
//                        break;
//                    case Piece::None:
//                        break;
//                }
//            }
//        }
//    }
//}
//
//void SchaakGUI::open() {
//    QFile file;
//    if (openFileToRead(file)) {
//        try {
//            QDataStream in(&file);
//
//            QString turn;
//            in >> turn;
//
//            if (turn == "TW" && g.getTurn() != zw::wit) {
//                g.changeTurn();
//            } else if (turn == "TB" && g.getTurn() != zw::zwart) {
//                g.changeTurn();
//            }
//
//            for (int r = 0; r < 8; r++) {
//                for (int k = 0; k < 8; k++) {
//                    QString piece;
//                    in >> piece;
//                    if (piece == ".") {
//                        g.setPiece(r, k, nullptr);
//                    } else {
//                        zw kleur = piece.endsWith("w") ? zw::wit : zw::zwart;
//                        if (piece.startsWith("P")) {
//                            g.setPiece(r, k, new Pion(kleur));
//                        } else if (piece.startsWith("R")) {
//                            g.setPiece(r, k, new Toren(kleur));
//                        } else if (piece.startsWith("K")) {
//                            g.setPiece(r, k, new Paard(kleur));
//                        } else if (piece.startsWith("B")) {
//                            g.setPiece(r, k, new Loper(kleur));
//                        } else if (piece.startsWith("H")) {
//                            g.setPiece(r, k, new Koning(kleur));
//                        } else if (piece.startsWith("Q")) {
//                            g.setPiece(r, k, new Koningin(kleur));
//                        } else {
//                            throw QString("Ongeldige formaat");
//                        }
//                    }
//                    if (in.status() != QDataStream::Ok) {
//                        throw QString("Ongeldig formaat");
//                    }
//                }
//            }
//            update();
//        } catch (QString& Q) {
//            message(Q);
//        }
//    }
//}


/// Save en open, door het bewaren van:
///     * het aantal zetten
///     * de index van de huidige zet
///     * alle zetten
void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);

        out << g.isAI_game();
        out << (int) g.allMoves().size();
        out << g.currentMoveIndex();
        for (const auto &move : g.allMoves()) {
            out << move.from.first << move.from.second;
            out << move.to.first << move.to.second;
        }
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);

            g.setStartBord();
            g.getMovePosition();
            g.clearMoves();

            bool isAI_game;
            int totalMoveSize;
            int currentMove;

            in >> isAI_game;
            in >> totalMoveSize;
            in >> currentMove;

            g.setAI_game(isAI_game);

            if (totalMoveSize == -1) {
                throw QString("Ongeldig formaat");
            }
            for (int i = 0; i < totalMoveSize; i++) {
                int fromRow = -1, fromCol = -1;
                int toRow = -1, toCol = -1;

                in >> fromRow >> fromCol;
                in >> toRow >> toCol;

                if (fromRow == -1 || fromCol == -1 || toRow == -1 || toCol == -1) {
                    throw QString("Ongeldig formaat");
                }

                g.move(g.getPiece(fromRow, fromCol), Position(toRow, toCol));
                g.changeTurn();
            }

            int currentGameMoveIndex = g.currentMoveIndex();
            while (currentGameMoveIndex != currentMove && currentMove >= 0 && currentGameMoveIndex >= 0) {
                g.undoMove();
                currentGameMoveIndex = g.currentMoveIndex();
            }

            update();
        } catch (QString& Q) {
            message(Q);
        }
    }
}


void SchaakGUI::undo() {
    g.undoMove();
    if (g.isAI_game()) {
        g.undoMove();
    }
    update();
}

void SchaakGUI::redo() {
    g.redoMove();
    if (g.isAI_game()) {
        g.redoMove();
    }
    update();
}

void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves() ? "T" : "F") +
                        (displayKills() ? "T" : "F") +
                        (displayThreats() ? "T" : "F");
    message(QString("Nieuwe settings : ") + visstring);
}
