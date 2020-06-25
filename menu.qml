import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {

    function newGame(){
        game.visible = true
        visible = false
        game.newGame()
        contButton.visible = true
    }

    function returnToGame() {
        game.visible = true
        visible = false
    }

    function menuReturned(){
        visible = true
        game.visible = false
    }

    function tenMin(){
        game.changeTime(600)
    }
    function thirtyMin(){
        game.changeTime(1800)
    }
    function oneHour() {
        game.changeTime(3600)
    }
    function twoHour(){
        game.changeTime(7200)
    }

    visible: true

    minimumWidth: 500
    maximumWidth: 500
    width: 500

    minimumHeight: 300
    maximumHeight: 300
    height: 300

    title: qsTr("Menu")

    ColumnLayout {

        Rectangle{
            width: 500
            height: 300
            color: "#cd853f"

            Rectangle{
                x: 50
                y: 25
                width: 400
                height: 250
                color: "#fffafa"
                Button {
                    id: contButton
                    text: "Return to game"
                    x: 10
                    y: 10
                    width: 380
                    height: 50
                    visible: false
                    onClicked: returnToGame()
                }

                Button {
                    text: "New Game"
                    x: 50
                    y: 70
                    width: 300
                    height: 50
                    onClicked: newGame()
                }

                Button {
                    text: "10 min"
                    x: 78
                    y: 130
                    width: 60
                    height: 50
                    onClicked: tenMin()
                }
                Button {
                    text: "30 min"
                    x: 139
                    y: 130
                    width: 60
                    height: 50
                    onClicked: thirtyMin()
                }
                Button {
                    text: "1 hour"
                    x: 200
                    y: 130
                    width: 60
                    height: 50
                    onClicked: oneHour()
                }
                Button {
                    text: "2 hour"
                    x: 261
                    y: 130
                    width: 60
                    height: 50
                    onClicked: twoHour()
                }

                Button {
                    text: "Quit"
                    x: 100
                    y: 190
                    width: 200
                    height: 50
                    onClicked: Qt.quit()
                }

            }
        }

        Game {
            id: game
            onReturnMenu: menuReturned()
        }
    }
}
