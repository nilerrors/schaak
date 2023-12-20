//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"

#include "guicode/fileIO.h"
#include "guicode/message.h"

// Constructor
SchaakGUI::SchaakGUI() : ChessWindow(nullptr) { update(); }

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    clearBoard();
    for (int rij = 0; rij < ROW_SIZE; rij++) {
        for (int kolom = 0; kolom < COL_SIZE; kolom++) {
            SchaakStuk* stuk = g.getPiece(rij, kolom);
            if (stuk != nullptr) setItem(rij, kolom, stuk);
        }
    }
}

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    removeAllMarking();
    update();

    SchaakStuk* stuk = g.getPiece(r, k);

    if (g.movePositionUnset()) {
        if (stuk == nullptr) return;
        if (stuk->getKleur() != g.getTurn()) return;

        g.setMovePosition(r, k);
        setTileSelect(r, k, true);
        for (const auto &zet : stuk->geldige_zetten(g)) {
            setTileFocus(zet.first, zet.second, true);
        }
    } else {
        SchaakStuk* moveStuk = g.getPiece(g.getMovePosition().first,
                                          g.getMovePosition().second);

        if (stuk == nullptr || (r != moveStuk->getPositie().first &&
                                k != moveStuk->getPositie().second)) {
            bool geldigeMove = false;
            std::vector<std::pair<int, int>> geldigeZetten = moveStuk->geldige_zetten(g);
            for (const auto &zet : geldigeZetten) {
                if (r == zet.first && k == zet.second) {
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
            g.clearMovePosition();
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
