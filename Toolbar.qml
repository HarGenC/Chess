import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    width: 600
    height: 50

    signal menu()
    signal newGame()

    Button {
        text: "New Game"
        width: 300; height: 50
        onClicked: newGame()
    }

    Button {
        text: "Menu"
        x: 300
        width: 300; height: 50
        onClicked: menu()
    }
}
