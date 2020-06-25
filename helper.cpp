#include "helper.h"
#include <iostream>

Helper::Helper(QObject *parent) : QObject(parent)
{

}

QVector<bool> Helper::loadBoard(){
    QVector<bool> color;

    for(int i  = 0; i < 64; i++)
    {
        int n = i / 8;
        (n + i % 8) % 2 == 0 ? color.push_back(true) : color.push_back(false);
    }
    return color;
}

void Helper::loadConfigsOfFields(QVector<int> ConfigsOfFields, QVector<int> WhoseFields) {
    figure.loadFields(ConfigsOfFields, WhoseFields);
}

QVector<bool> Helper::passingParameters(int x1, int y1, int config, int x2, int y2){
    return figure.movement(x1, y1, config, x2, y2);
}

QVector<int> Helper::takeConfigs(){
    return figure.TakeFields();
}
QVector<int> Helper::takeColors(){
    return figure.TakeColors();
}
void Helper::restart() {
    figure.restart();
}






/*
 * Сделать:
 * 0)Создание поля игры +
 * 1)Отдельный класс или объект под флаги для ладьей, королей +
 * 1.1)Активация флагов +
 * 2)Проходная пешка +-(Без выбора)
 * 3)Длинная рокировка +
 * 4)Короткая рокировка +
 * 5)Особый случай поедания пешки пешкой +
 * 6)Проверка на правильность хода, что не будет шаха +
 * 7)Апгрейд рокировок и остальной дичи(особое поедание пешки, при котором возможен шах) +
 * 8)шах и мат, пат(Проверка всего поля, есть ли ход, при котором шаха не будет; Есть ли ход любой) +
 * 9)Ход по очереди +
 * 10)Время для игроков
 * 11)Остальные плюшки ...
 */
