#ifndef FIGURE_MOVEMENT_H
#define FIGURE_MOVEMENT_H

#include <QObject>

struct FigureFlags {
    bool whiteKing = false;
    bool blackKing = false;
    bool lWhiteRook = false;
    bool rWhiteRook = false;
    bool lBlackRook = false;
    bool rBlackRook = false;
};

struct Last {
    int x1;
    int y1;
    int x2;
    int y2;
    int config;
};

struct LocKing {
    int x;
    int y;
};


class FigureMovement
{
public:
    FigureMovement();
    FigureMovement(const QVector<int>& fields);
    QVector<bool> movement(int x1, int y1, int config, int x2, int y2);
    QVector<int> TakeFields();
    QVector<int> TakeColors();
    void loadFields(QVector<int> ConfigsOfFields, QVector<int> WhoseFields);
    void activateFlags(int x1, int y1, int config);
    bool checkMovementPawn(QVector<int> &configs, int x1, int y1, int x2, int y2, int player, int &specialCase);
    void restart();
    void moveKing(int x1, int y1, int x2, int y2);
    bool checkShah(int x1, int y1, int x2, int y2, int player);
    bool checkMovementKing(int x1, int y1, int x2, int y2, int &specialCase);
    void castling(int specialCase);
    void specialCasePawn (int specialCase);
    bool checkTryMove(int x1, int y1, int x2, int y2, int config);
    void undoSpecialCasePawn (int specialCase);
    bool isMate(int player);

private:
    QVector<int> ConfigOfFields;
    QVector<int> WhoseFields;
    FigureFlags flags;
    Last lastMove;
    LocKing WhiteKing;
    LocKing BlackKing;
};

#endif // FIGURE_MOVEMENT_H
