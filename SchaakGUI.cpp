//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"

#include "guicode/fileIO.h"
#include "guicode/message.h"
#include <iostream>

// Constructor
SchaakGUI::SchaakGUI() : ChessWindow(nullptr) { update(); }

std::string pieceToString(Piece piece);

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
    } else if (g.schaakmat(zw::zwart)) {
        g.endGame();
        message("Schaakmat! Wit heeft gewonnen.");
    } else if (g.pat(zw::wit) || g.pat(zw::zwart)) {
        g.endGame();
        message("Pat! Gelijkspel.");
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

    std::cout << "Geklikte positie: (" << std::to_string(r) << ", " << std::to_string(k) << ")" << std::endl;
    std::cout << "\tEr staat: " << (stuk == nullptr ? "Niets" :
                                    (stuk->getKleur() == zw::wit ? "wit " : "zwart ") +
                                        pieceToString(stuk->piece()))
                                << std::endl;

    if (g.movePositionUnset()) {
        g.setMovePosition(r, k);

        removeAllMarking();
    } else {
        SchaakStuk* moveStuk = g.getPiece(g.getMovePosition().first,
                                          g.getMovePosition().second);

        if (r == moveStuk->getPositie().first && k == moveStuk->getPositie().second) {
            g.clearMovePosition();
        } else if (stuk == nullptr || (stuk != nullptr && stuk->getKleur() != moveStuk->getKleur())) {
            bool geldigeMove = false;
            std::vector<std::pair<int, int>> geldigeZetten = moveStuk->geldige_zetten(g);
            for (const auto &zet : geldigeZetten) {
                if (r == zet.first && k == zet.second) {
                    std::cout << "Beweeg stuk: "
                    << (moveStuk->getKleur() == zw::wit ? "wit " : "zwart ")
                    << pieceToString(moveStuk->piece())
                    << " naar (" << std::to_string(r) << ", " << std::to_string(k) << ")"
                    << std::endl;

                    geldigeMove = true;
                    g.move(moveStuk, r, k);
                    g.clearMovePosition();
                    g.changeTurn();
                    break;
                }
            }
            if (!geldigeMove) {
                message("Deze zet is ongeldig.");
            }
        } else {
            message("Deze zet is ongeldig.");
        }
    }

    removeAllMarking();
    if (displayThreats()) {
        // kleurt alle bedreigde schaakstukken
        // van beide kanten
        for (const auto &zet : g.threats()) {
            setPieceThreat(zet.first, zet.second, true);
        }
    }
    if (!g.movePositionUnset()) {
        SchaakStuk* moveStuk = g.getPiece(g.getMovePosition().first,
                                          g.getMovePosition().second);

        setTileSelect(g.getMovePosition().first,g.getMovePosition().second, true);
        if (displayKills()) {
            for (const auto &zet : g.kills(moveStuk)) {
                setTileThreat(zet.first, zet.second, true);
            }
        }
        if (displayMoves()) {
            for (const auto &zet : moveStuk->geldige_zetten(g)) {
                setTileFocus(zet.first, zet.second, true);
            }
        }
    }

    update();
}

void SchaakGUI::newGame() {}

void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb")
            << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for (int i = 0; i < 8; i++) {
            out << QString("Pb");
        }
        for (int r = 3; r < 7; r++) {
            for (int k = 0; k < 8; k++) {
                out << QString(".");
            }
        }
        for (int i = 0; i < 8; i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw")
            << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r = 0; r < 8; r++) {
                for (int k = 0; k < 8; k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status() != QDataStream::Ok) {
                        throw QString("Ongeldig formaat");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}

void SchaakGUI::undo() { message("UNDO"); }

void SchaakGUI::redo() { message("REDO"); }

void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves() ? "T" : "F") +
                        (displayKills() ? "T" : "F") +
                        (displayThreats() ? "T" : "F");
    message(QString("Nieuwe settings : ") + visstring);
}
