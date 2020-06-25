#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include "figureMovement.h"

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

signals:

public slots:
    QVector<bool> loadBoard();
    void loadConfigsOfFields(QVector<int> ConfigsOfFields, QVector<int> whoseFields);
    QVector<bool> passingParameters(int x1, int y1, int config, int x2, int y2);
    QVector<int> takeConfigs();
    QVector<int> takeColors();
    void restart ();

private:
    FigureMovement figure;
};

#endif // HELPER_H
