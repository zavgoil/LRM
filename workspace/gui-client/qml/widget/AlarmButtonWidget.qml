import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

import app

Rectangle {
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    Layout.preferredHeight: Math.min(parent.height, parent.width) * 0.4
    Layout.preferredWidth: height

    color: "red"
    radius: height / 2

    MouseArea {
        anchors.fill: parent
        onClicked: {
            AppBackend.alert()
        }
    }

    Text {
        text: "Сигнализация"
        anchors.centerIn: parent
        color: "white" 
        font.pixelSize: 30 
    }
}