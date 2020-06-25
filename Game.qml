import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12


Window {
    id: game
    minimumWidth: 800
    maximumWidth: 800
    width: 800

    minimumHeight: 650
    maximumHeight: 650
    height: 650

    signal returnMenu()

    function newGame(){
        chess.newGame()
    }

    function changeTime (time){
        chess.time = time
    }

    Chess {
        id: chess
        onChangeTime: information_table.is_white_move = is_white_move
        onRestoreTime: {
            information_table.whiteTime = time
            information_table.blackTime = time
            information_table.is_white_move = 2
        }
    }

    InformationTable {
        id: information_table
        x: 600
    }

    Toolbar {
        y: 600
        onMenu: returnMenu()
        onNewGame: chess.newGame()
    }
}
