import QtQuick 2.0

Rectangle {
    width: 200; height: 650
    color: "#d2691e"
    function whiteLose() {
        time.who_lose_time = true
        time.visible = true
    }

    function blackLose() {
        time.who_lose_time = false
        time.visible = true
    }

    property int is_white_move: 2
    property int whiteTime: 3600
    property int blackTime: 3600

    Timer {
        id: white_timer
        repeat: true
        running: is_white_move === 2 ? true : false

        onTriggered: {
            if(whiteTime !== 0){
            whiteTime -= 1
            } else {
                whiteLose()
                is_white_move === 0
            }
        }
    }

    Timer {
        id: black_timer
        repeat: true
        running: is_white_move === 1 ? true : false

        onTriggered: {
            if(blackTime !== 0){
            blackTime -= 1
            } else {
                blackLose()
                is_white_move === 0
            }
        }
    }

    Rectangle {
        width: 200; height: 30
        id: black_time

        border.width: 1

        Text {
            text: "White Time: " + whiteTime
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

    }
    Rectangle {
        y: 29
        width: 200; height: 30
        id: white_time

        border.width: 1

        Text {
            text: "Black Time: " + blackTime
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Time {
        id:time
    }

}
