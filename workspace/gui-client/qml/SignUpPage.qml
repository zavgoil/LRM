import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "./widget"

GridLayout {
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    width: parent.width
    height: parent.height

    columns: 1

    SignUpWidget{
    }
    Button{
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        text:"Войти"
        onClicked: changePage("SignInPage.qml")
    }

}
