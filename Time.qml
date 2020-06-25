import QtQuick 2.0
import QtQuick.Window 2.12

Window {
    property bool who_lose_time: false
    title: who_lose_time ? "Time, Black Win!!!" : "Time, White Win!!!"
    visible: false

    width: 250
    minimumWidth:250
    maximumWidth:250

    height: 40
    minimumHeight: 40
    maximumHeight: 40
}
