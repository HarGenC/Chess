import QtQuick 2.0
import QtQuick.Layouts 1.12

GridLayout {
    width: 600
    height: 600
    columns: 8
    rows: 8

    columnSpacing: 0
    rowSpacing: 0

    signal changeTime(int is_white_move)
    signal restoreTime(int time)


    property bool firstChoice: true
    property int x1: 0
    property int y1: 0
    property int config1: 0
    property int player1: 0
    property int is_white_move: 2
    property int time: 3600

    function newGame() {
        const fieldColor = helper.loadBoard()
        for(let i = 0; i < fieldColor.length; i++)
            fields.itemAt(i).colorWhite = fieldColor[i]

        for(let i = 0; i < fieldColor.length; i++){
            fields.itemAt(i).oy = i / 8
            fields.itemAt(i).ox = i % 8
            fields.itemAt(i).config = 0
            fields.itemAt(i).player = 0
    }
        is_white_move = 2
        generatorGame()
        takeConfigs()
        restoreTime(time)
    }

    function takeConfigs(){
        const configOfFields = []
        const whoseFields = []
        for(let i = 0; i <fields.count; i++)
            configOfFields.push(fields.itemAt(i).config)
        for(let i = 0; i <fields.count; i++)
            whoseFields.push(fields.itemAt(i).player)

        helper.loadConfigsOfFields(configOfFields, whoseFields)
    }


    function transferData(x2, y2, config2, player2) {
        if(player2 === is_white_move || firstChoice !== true){
            if(player2 !== 0 || firstChoice !== true){
                if(firstChoice === true || player1 === player2) {
                    fields.itemAt(y1 * 8 + x1).selected = false
                    x1 = x2
                    y1 = y2
                    config1 = config2
                    player1 = player2
                    firstChoice = false
                    fields.itemAt(y2 * 8 + x2).selected = true
                }
                else {
                    fields.itemAt(y1 * 8 + x1).selected = false
                    firstChoice = true
                    const act = helper.passingParameters(x1, y1, config1, x2, y2)
                    if (act[0] === true){
                        const configOfFields = helper.takeConfigs()
                        for(let i = 0; i < fields.count; i++)
                            fields.itemAt(i).config = configOfFields[i]

                        const whoseFields = helper.takeColors()
                        for(let i = 0; i < fields.count; i++)
                            fields.itemAt(i).player = whoseFields[i]

                        if(is_white_move === 2){
                            is_white_move = 1
                            changeTime(is_white_move)
                        } else {
                            is_white_move = 2
                            changeTime(is_white_move)
                        }
                        if(act[1] === true){
                            checkmate.who_win = act[3]
                            checkmate.visible = true

                        } else if(act[2] === true) {
                            stalemate.who_stale_mate = act[3]
                            stalemate.visible = true
                                }
                    }
                }
            }
        }

    }


    Repeater{
        id: fields
        model: 64

        Field {
            onTakeInfo: {
                transferData(ox, oy, config, player)
            }
        }
    }



    function generatorGame(){

        for(let i = 0; i < 8; i++){
            fields.itemAt(8 + i).config = 1
            fields.itemAt(8 + i).player = 1

            fields.itemAt(48 + i).config = 1
            fields.itemAt(48 + i).player = 2
        }

        fields.itemAt(0).config = 4
        fields.itemAt(0).player = 1
        fields.itemAt(7).config = 4
        fields.itemAt(7).player = 1

        fields.itemAt(56).config = 4
        fields.itemAt(56).player = 2
        fields.itemAt(63).config = 4
        fields.itemAt(63).player = 2

        fields.itemAt(1).config = 3
        fields.itemAt(1).player = 1
        fields.itemAt(6).config = 3
        fields.itemAt(6).player = 1

        fields.itemAt(57).config = 3
        fields.itemAt(57).player = 2
        fields.itemAt(62).config = 3
        fields.itemAt(62).player = 2

        fields.itemAt(2).config = 2
        fields.itemAt(2).player = 1
        fields.itemAt(5).config = 2
        fields.itemAt(5).player = 1

        fields.itemAt(58).config = 2
        fields.itemAt(58).player = 2
        fields.itemAt(61).config = 2
        fields.itemAt(61).player = 2

        fields.itemAt(3).config = 5
        fields.itemAt(3).player = 1
        fields.itemAt(4).config = 6
        fields.itemAt(4).player = 1

        fields.itemAt(59).config = 5
        fields.itemAt(59).player = 2
        fields.itemAt(60).config = 6
        fields.itemAt(60).player = 2

        helper.restart()
    }

    CheckMate {
        id: checkmate
    }
    StaleMate {
        id: stalemate
    }
}
