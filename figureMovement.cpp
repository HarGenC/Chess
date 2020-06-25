#include "figureMovement.h"
#include <iostream>

FigureMovement::FigureMovement()
{

}

FigureMovement::FigureMovement(const QVector<int>& fields){
    for(int i = 0; i < fields.count(); i++)
        this->ConfigOfFields.push_back(fields[i]);
}

void FigureMovement::loadFields(QVector<int> ConfigsOfFields, QVector<int> WhoseFields) {
    this->ConfigOfFields.clear();
    this->WhoseFields.clear();
    for(int i = 0; i < ConfigsOfFields.count(); i++)
        this->ConfigOfFields.push_back(ConfigsOfFields[i]);
    for(int i = 0; i < WhoseFields.count(); i++)
        this->WhoseFields.push_back(WhoseFields[i]);
    WhiteKing.x = 4;
    WhiteKing.y = 7;
    BlackKing.x = 4;
    BlackKing.y = 0;
}

bool checkMovementBishop(QVector<int> &configs, int x1, int y1, int x2, int y2);
bool checkMovementKnight(int x1, int y1, int x2, int y2);
bool checkMovementRook(QVector<int> &configs, int x1, int y1, int x2, int y2);
bool checkMovementQueen(QVector<int> &configs, int x1, int y1, int x2, int y2);

void move(QVector<int> &configs, QVector<int> &ColorPlayer, int x1, int y1, int config, int x2, int y2);

QVector<bool> FigureMovement::movement(int x1, int y1, int config, int x2, int y2) {
    bool can_move = false;
    int specialCase = 0;
    switch (config) {
    case 1: // Пешка
        if(!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1])) {
            can_move = checkMovementPawn(ConfigOfFields, x1, y1, x2, y2, WhoseFields[y1 * 8 + x1], specialCase);
            if (can_move) {
                if (specialCase != 0) {
                    specialCasePawn(specialCase);
                    if (!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1]))
                    {
                        move(ConfigOfFields, WhoseFields, x1, y1, config, x2, y2);
                    } else {
                    undoSpecialCasePawn(specialCase);
                    }
                } else if (y2 == 0 || y2 == 7) {
                    move(ConfigOfFields, WhoseFields, x1, y1, config, x2, y2);
                    ConfigOfFields[y2 * 8 + x2] = 5;
                } else {
                    move(ConfigOfFields, WhoseFields, x1, y1, config, x2, y2);
                }
            }
        }
        break;

    case 2: // Слон
        if(!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1])) {
            can_move = checkMovementBishop(ConfigOfFields, x1, y1, x2, y2);
            if(can_move) {
                move(ConfigOfFields, WhoseFields, x1, y1, config, x2, y2);
            }
        }
        break;

    case 3: // Конь
        if(!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1])) {
            can_move = checkMovementKnight(x1, y1, x2, y2);
            if(can_move ) {
                move(ConfigOfFields, WhoseFields, x1, y1, config, x2, y2);
            }
        }
        break;

    case 4: // Ладья
        if(!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1])) {
            can_move = checkMovementRook(ConfigOfFields, x1, y1, x2, y2);
            if(can_move) {
                move(ConfigOfFields, this->WhoseFields, x1, y1, config, x2, y2);
                activateFlags(x1, y1, config);
            }
        }
        break;

    case 5: // Ферзь
        if(!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1])) {
            can_move = checkMovementQueen(ConfigOfFields, x1, y1, x2, y2);
            if(can_move) {
                move(ConfigOfFields, this->WhoseFields, x1, y1, config, x2, y2);
            }
        }
        break;

    case 6: // Король
        if(!checkShah(x1, y1, x2, y2, WhoseFields[y1 * 8 + x1])){
            can_move = checkMovementKing(x1, y1, x2, y2, specialCase);
            if(can_move) {
                moveKing(x1, y1, x2, y2);
                move(ConfigOfFields, WhoseFields, x1, y1, config, x2, y2);
                if(specialCase != 0) castling(specialCase);
                activateFlags(x1, y1, config);
            }
        }
        break;
    }
    specialCase = 0;
    QVector<bool> information;
    information.push_back(can_move);
    information.push_back(false); // это мат?
    information.push_back(false); // это пат?
    information.push_back(false); // цвет игрока т.е. кому поставили мат false - чёрный, true - белый

    if (can_move) {
        lastMove.x1 = x1;
        lastMove.x2 = x2;
        lastMove.y1 = y1;
        lastMove.y2 = y2;
        lastMove.config = config;

        if (isMate(WhoseFields[y2 * 8 + x2])){
            if (WhoseFields[y2 * 8 + x2] == 2){
                if (checkShah(BlackKing.x, BlackKing.y, BlackKing.x, BlackKing.y, 1)){
                    information[1] = true;
                } else {
                    specialCase = 2;
                    information[2] = true;
                }
            } else {
                if (checkShah(WhiteKing.x, WhiteKing.y, WhiteKing.x, WhiteKing.y, 2)){
                    information[1] = true;
                    information[3] = true;
                    specialCase = 3;
                } else {
                    specialCase = 4;
                    information[2] = true;
                    information[3] = true;
                }
            }
    }
    }
    return information;
}

bool FigureMovement::checkMovementPawn(QVector<int> &configs, int x1, int y1, int x2, int y2, int player, int &specialCase){
    // player 2 белый, player 1 - чёрный
    if(player == 2){
        if (x1 == x2
         && y1 == 6
         && y2 == 4
         && configs[y2 * 8 + x1] == 0
         && configs[(y2 + 1) * 8 + x1] == 0) {
            return true;
        }
        if (y1 == y2 + 1
         && x1 == x2
         && configs[y2 * 8 + x1] == 0) {
            return true;
        }
        if (y1 == y2 + 1
         && ((x1 - 1 == x2 && configs[y2 * 8 + x2] != 0) || (x1 + 1 == x2 && configs[y2 * 8 + x2] != 0))) return true;
        if (lastMove.y1 == 1
         && lastMove.y2 == 3
         && lastMove.config == 1
         && y1 == 3 && y2 == 2
         && lastMove.x1 == x2
         && (x1 == lastMove.x1 - 1 || x1 == lastMove.x1 + 1)){
            specialCase = 1;
            return true;
        }
    } else {
        if (x1 == x2
         && y1 == 1
         && y2 == 3
         && configs[y2 * 8 + x1] == 0
         && configs[(y2 - 1) * 8 + x1] == 0) {
            return true;
        }
        if (y1 == y2 - 1
         && x1 == x2
         && configs[y2 * 8 + x1] == 0) {
            return true;
        }
        if (y1 == y2 - 1
        && ((x1 - 1 == x2 && configs[y2 * 8 + x2] != 0) || (x1 + 1 == x2 && configs[y2 * 8 + x2] != 0))) {
            return true;
        }
        if (lastMove.y1 == 6
         && lastMove.y2 == 4
         && lastMove.config == 1
         && y1 == 4 && y2 == 5
         && lastMove.x1 == x2
         && (x1 == lastMove.x1 - 1 || x1 == lastMove.x1 + 1)){
            specialCase = 2;
            return true;
        }
    }
    return false;
}

bool checkMovementBishop(QVector<int> &configs, int x1, int y1, int x2, int y2){
    if(abs(x1 - x2) == abs(y1 - y2)){
        if (x1 - x2 < 0){
            if (y1 - y2 < 0){
                for(int i = 1; (y1 + i) * 8 + x1 + i != y2 * 8 + x2; i++){
                    if(configs[(y1 + i) * 8 + x1 + i] != 0) return false;
                }
                return true;
            } else {
                for(int i = 1; (y1 - i) * 8 + x1 + i != y2 * 8 + x2; i++){
                    if(configs[(y1 - i) * 8 + x1 + i] != 0) return false;
                }
                return true;
            }
        } else if (y1 - y2 < 0){
            for(int i = 1; (y1 + i) * 8 + x1 - i != y2 * 8 + x2; i++){
                if(configs[(y1 + i) * 8 + x1 - i] != 0) return false;
            }
            return true;
        } else {
            for(int i = 1; (y1 - i) * 8 + x1 - i != y2 * 8 + x2; i++){
                if(configs[(y1 - i) * 8 + x1 - i] != 0) return false;
            }
            return true;
        }
    }
    return false;
}

bool checkMovementKnight(int x1, int y1, int x2, int y2){
    if (((y1 == y2 - 2 || y1 == y2 + 2) && (x1 == x2 + 1 || x1 == x2 - 1))
     || ((x1 == x2 - 2 || x1 == x2 + 2)
     && (y1 == y2 + 1 || y1 == y2 - 1))) return true;
    return false;
}

bool checkMovementRook(QVector<int> &configs, int x1, int y1, int x2, int y2){
    if(x1 - x2 != 0 && y1 - y2 != 0) return false;

    if(abs(x1 - x2) != 0){
        if(x1 - x2 < 0){
            for(int i = 1; x2 - i != x1; i++){
                if(configs[y1 * 8 + x1 + i] != 0) return false;
            }
            return true;
        }
        else {
            for(int i = 1; x2 + i != x1; i++){
                if(configs[y1 * 8 + x1 - i] != 0) return false;
            }
            return true;
        }
    }
    else if(y1 - y2 < 0){
        for(int i = 1; y2 - i != y1; i++){
            if(configs[(y1 + i) * 8 + x1] != 0) return false;
        }
        return true;
    }
    else {
        for(int i = 1; y2 + i != y1; i++){
            if(configs[(y1 - i) * 8 + x1] != 0) return false;
        }
        return true;
    }

    return false;
}

bool checkMovementQueen(QVector<int> &configs, int x1, int y1, int x2, int y2){
    if(checkMovementBishop(configs, x1, y1, x2, y2) == true) return true;
    else if(checkMovementRook(configs, x1, y1, x2, y2) == true) return true;
    return false;
}

bool FigureMovement::checkMovementKing(int x1, int y1, int x2, int y2, int &specialCase){
    if(WhoseFields[y1 * 8 + x1] == 2){
        if (flags.whiteKing == false
         && flags.rWhiteRook == false
         && WhoseFields[63] == 2
         && ConfigOfFields[63] == 4
         && WhoseFields[61] == 0
         && x2 == 6
         && y2 == 7
         && !checkShah(x1, y1, x1, y1, 2)
         && !checkShah(x1, y1, x1 + 1, y1, 2)) {
            specialCase = 1;
            return true;
        }

        if (flags.whiteKing == false
         && flags.lWhiteRook == false
         && WhoseFields[56] == 2
         && ConfigOfFields[56] == 4
         && WhoseFields[57] == 0
         && WhoseFields[59] == 0
         && x2 == 2
         && y2 == 7
         && !checkShah(x1, y1, x1, y1, 2)
         && !checkShah(x1, y1, x1 - 1, y1, 2)) {
            specialCase = 3;
            return true;
        }
    } else {
        if (flags.blackKing == false
         && flags.rBlackRook == false
         && WhoseFields[7] == 1
         && ConfigOfFields[7] == 4
         && WhoseFields[5] == 0
         && x2 == 6
         && y2 == 0
         && !checkShah(x1, y1, x1, y1, 1)
         && !checkShah(x1, y1, x1 + 1, y1, 1)) {
            specialCase = 2;
            return true;
        }
        if (flags.blackKing == false
         && flags.lBlackRook == false
         && WhoseFields[0] == 1
         && ConfigOfFields[0] == 4
         && WhoseFields[1] == 0
         && WhoseFields[3] == 0
         && x2 == 2
         && y2 == 0
         && !checkShah(x1, y1, x1, y1, 1)
         && !checkShah(x1, y1, x1 - 1, y1, 1)) {
            specialCase = 4;
            return true;
        }
    }

    if(abs(x1 - x2) > 1) return false;
    else if(abs(y1 - y2) > 1) return false;
    else return true;
}

void move(QVector<int> &configs, QVector<int> &ColorPlayer, int x1, int y1, int config, int x2, int y2){
    configs[y1 * 8 + x1] = 0;
    configs[y2 * 8 + x2] = config;
    ColorPlayer[y2 * 8 + x2] = ColorPlayer[y1 * 8 + x1];
    ColorPlayer[y1 * 8 + x1] = 0;
}

QVector<int> FigureMovement::TakeFields(){
    return ConfigOfFields;
}

QVector<int> FigureMovement::TakeColors(){
    return WhoseFields;
}

void FigureMovement::restart(){
    flags.blackKing = false;
    flags.whiteKing = false;
    flags.lBlackRook = false;
    flags.lWhiteRook = false;
    flags.rBlackRook = false;
    flags.lBlackRook = false;
}

void FigureMovement::activateFlags(int x1, int y1, int config) {
    if(config == 4){
        if (x1 == 0 && y1 == 0) {
            flags.lBlackRook = true;
            return ;
        } else if (x1 == 7 && y1 == 0) {
            flags.rBlackRook = true;
            return ;
        } else if (x1 == 0 && y1 == 7) {
            flags.lWhiteRook = true;
            return ;
        } else if (x1 == 7 && y1 == 7) {
            flags.rWhiteRook = true;
            return ;
        }
        return ;
    }

    if (config == 6){
        if (x1 == 4 && y1 == 0) {
            flags.blackKing = true;
            return ;
        } else if (x1 == 4 && y1 == 7) {
            flags.whiteKing = true;
            return ;
        }
        return ;
    }

}

void FigureMovement::moveKing(int x1, int y1, int x2, int y2) {
    if(WhoseFields[y1 * 8 + x1] == 2) {
        WhiteKing.x = x2;
        WhiteKing.y = y2;
    } else {
        BlackKing.x = x2;
        BlackKing.y = y2;
    }
}

bool FigureMovement::checkShah(int x1, int y1, int x2, int y2, int player){
    int x, y;

    int tempPlayer = ConfigOfFields[y2 * 8 + x2];
    int tempWho = WhoseFields[y2 * 8 + x2];
    if(ConfigOfFields[y1 * 8 + x1] == 6){
        moveKing(x1, y1, x2, y2);
    }
    WhoseFields[y2 * 8 + x2] = WhoseFields[y1 * 8 + x1];
    ConfigOfFields[y2 * 8 + x2] = ConfigOfFields[y1 * 8 + x1];
    WhoseFields[y1 * 8 + x1] = 0;
    ConfigOfFields[y1 * 8 + x1] = 0;

    for(int i = 0; i < 64; i++){
        x = i % 8;
        y = i / 8;
        if(player == 2){
            if(WhoseFields[i] == 1) if(checkTryMove(x, y, WhiteKing.x, WhiteKing.y, ConfigOfFields[i])) {

                if(ConfigOfFields[y2 * 8 + x2] == 6){
                    moveKing(x2, y2, x1, y1);
                }
                WhoseFields[y1 * 8 + x1] = WhoseFields[y2 * 8 + x2];
                ConfigOfFields[y1 * 8 + x1] = ConfigOfFields[y2 * 8 + x2];
                ConfigOfFields[y2 * 8 + x2] = tempPlayer;
                WhoseFields[y2 * 8 + x2] = tempWho;

                return true;
            }
        } else {
            if(WhoseFields[i] == 2) if(checkTryMove(x, y, BlackKing.x, BlackKing.y, ConfigOfFields[i])) {

                if(ConfigOfFields[y2 * 8 + x2] == 6){
                    moveKing(x2, y2, x1, y1);
                }
                WhoseFields[y1 * 8 + x1] = WhoseFields[y2 * 8 + x2];
                ConfigOfFields[y1 * 8 + x1] = ConfigOfFields[y2 * 8 + x2];
                ConfigOfFields[y2 * 8 + x2] = tempPlayer;
                WhoseFields[y2 * 8 + x2] = tempWho;

                return true;
            }
        }
    }
    if(ConfigOfFields[y2 * 8 + x2] == 6){
        moveKing(x2, y2, x1, y1);
    }
    WhoseFields[y1 * 8 + x1] = WhoseFields[y2 * 8 + x2];
    ConfigOfFields[y1 * 8 + x1] = ConfigOfFields[y2 * 8 + x2];
    ConfigOfFields[y2 * 8 + x2] = tempPlayer;
    WhoseFields[y2 * 8 + x2] = tempWho;
    return false;
}

bool FigureMovement::checkTryMove(int x1, int y1, int x2, int y2, int config){
    bool can = false;
    int temp;
    switch (config) {
    case 1: // Пешка
        can = checkMovementPawn(ConfigOfFields, x1, y1, x2, y2, WhoseFields[y1 * 8 + x1], temp);
        break;

    case 2: // Слон
        can = checkMovementBishop(ConfigOfFields, x1, y1, x2, y2);
        break;

    case 3: // Конь
        can = checkMovementKnight(x1, y1, x2, y2);
        break;

    case 4: // Ладья
        can = checkMovementRook(ConfigOfFields, x1, y1, x2, y2);
        break;

    case 5: // Ферзь
        can = checkMovementQueen(ConfigOfFields, x1, y1, x2, y2);
        break;

    case 6: // Король
        can = checkMovementKing(x1, y1, x2, y2, temp);
        break;
    }
    return can;
}

void FigureMovement::castling(int specialCase){
    switch (specialCase) {
    case 1:
        flags.whiteKing = true;
        ConfigOfFields[63] = 0;
        WhoseFields[63] = 0;
        ConfigOfFields[61] = 4;
        WhoseFields[61] = 2;
        break;

    case 2:
        flags.blackKing = true;
        ConfigOfFields[7] = 0;
        WhoseFields[7] = 0;
        ConfigOfFields[5] = 4;
        WhoseFields[5] = 1;
        break;

    case 3:
        flags.whiteKing = true;
        ConfigOfFields[56] = 0;
        WhoseFields[56] = 0;
        ConfigOfFields[59] = 4;
        WhoseFields[59] = 2;
        break;

    case 4:
        flags.blackKing = true;
        ConfigOfFields[0] = 0;
        WhoseFields[0] = 0;
        ConfigOfFields[3] = 4;
        WhoseFields[3] = 1;
        break;
    }
}

void FigureMovement::specialCasePawn (int specialCase){
    switch (specialCase) {
    case 1:
        ConfigOfFields[lastMove.y2 * 8 + lastMove.x2] = 0;
        WhoseFields[lastMove.y2 * 8 + lastMove.x2] = 0;
        break;

    case 2:
        ConfigOfFields[lastMove.y2 * 8 + lastMove.x2] = 0;
        WhoseFields[lastMove.y2 * 8 + lastMove.x2] = 0;
        break;
    }
}

void FigureMovement::undoSpecialCasePawn (int specialCase){
    switch (specialCase) {
    case 1:
        ConfigOfFields[lastMove.y2 * 8 + lastMove.x2] = 1;
        WhoseFields[lastMove.y2 * 8 + lastMove.x2] = 1;
        break;

    case 2:
        ConfigOfFields[lastMove.y2 * 8 + lastMove.x2] = 1;
        WhoseFields[lastMove.y2 * 8 + lastMove.x2] = 2;
        break;
    }
}


bool FigureMovement::isMate(int player) {
    int x1, y1, x2, y2;
    if(player == 2){
        for(int i = 0; i < 64; ++i){
            x1 = i % 8;
            y1 = i / 8;
            if(WhoseFields[i] == 1){
                for(int j = 0; j < 64; ++j){
                    x2 = j % 8;
                    y2 = j / 8;
                    if ((x1 == x2 && y1 == y2) || WhoseFields[i] == WhoseFields[j]){
                        continue;
                    }
                    if (checkTryMove(x1, y1, x2, y2, ConfigOfFields[i])
                     && !checkShah(x1, y1, x2, y2, WhoseFields[i])){
                        return false;
                    }
                }
            }
        }
    } else {
        for(int i = 0; i < 64; ++i){
            x1 = i % 8;
            y1 = i / 8;
            if(WhoseFields[i] == 2){
                for(int j = 0; j < 64; ++j){
                    x2 = j % 8;
                    y2 = j / 8;
                    if ((x1 == x2 && y1 == y2) || WhoseFields[i] == WhoseFields[j]){
                        continue;
                    }
                    if (checkTryMove(x1, y1, x2, y2, ConfigOfFields[i])
                     && !checkShah(x1, y1, x2, y2, WhoseFields[i])){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
