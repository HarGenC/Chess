import QtQuick 2.0

Rectangle {
    width: 75; height: 75

    property int player: 0 // 0 - поле, 1 - чёрный, 2 - белый
    property bool colorWhite: false
    property int config: 0 // 0 - ничего, 1 - пешка, 2 - слон, 3 - конь ...
    property int ox: 0
    property int oy: 0
    property bool selected: false

    signal takeInfo()
    color: colorWhite ? "#fffafa" : "#cd853f"

    border.width: selected ? 2 : 0
    border.color: "green"


    Text {
        visible: ox === 0
        text: oy + 1
    }

    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 0
        text: 'a'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 1
        text: 'b'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 2
        text: 'c'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 3
        text: 'd'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 4
        text: 'e'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 5
        text: 'f'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 6
        text: 'g'
    }
    Text {
        x: 2
        y: 60
        visible: oy === 7 && ox === 7
        text: "h"
    }

    Image {
        id: pawn
       visible: config === 1
       source: player === 2 ? "/Figures/WhitePawn.png" : "/Figures/BlackPawn.png"
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
   }

    Image {
        id: bishop
       visible: config === 2
       source: player === 2 ? "/Figures/WhiteBishop.png" : "/Figures/BlackBishop.png"
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
   }

    Image {
        id: knight
       visible: config === 3
       source: player === 2 ? "/Figures/WhiteKnight.png" : "/Figures/BlackKnight.png"
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
   }


     Image {
         id: rook
        visible: config === 4
        source: player === 2 ? "/Figures/WhiteRook.png" : "/Figures/BlackRook.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

     Image {
         id: queen
        visible: config === 5
        source: player === 2 ? "/Figures/WhiteQueen.png" : "/Figures/BlackQueen.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

     Image {
         id: king
        visible: config === 6
        source: player === 2 ? "/Figures/WhiteKing.png" : "/Figures/BlackKing.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        anchors.fill: parent
        onClicked: takeInfo()
    }
}
