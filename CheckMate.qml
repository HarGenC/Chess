import QtQuick 2.0
import QtQuick.Window 2.12

Window {
    property bool who_win: false
    title: who_win ? "CheckMate, Black Win!!!" : "CheckMate, White Win!!!"
    visible: false

    width: 500
    minimumWidth:500
    maximumWidth:500

    height: 40
    minimumHeight: 40
    maximumHeight: 40
}
