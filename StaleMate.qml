import QtQuick 2.0
import QtQuick.Window 2.12

Window {
    property bool who_stale_mate: false
    title: who_stale_mate ? "StaleMate for White, Draw!!!" : "StaleMate for Black, Draw!!!"
    visible: false

    width: 500
    minimumWidth:500
    maximumWidth:500

    height: 40
    minimumHeight: 40
    maximumHeight: 40
}
