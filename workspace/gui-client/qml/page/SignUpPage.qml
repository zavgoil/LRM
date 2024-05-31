import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "./../widget"

GridLayout{
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    height: parent.height
    width: parent.width

    columns: 1

    SignUpWidget{
    }
}

