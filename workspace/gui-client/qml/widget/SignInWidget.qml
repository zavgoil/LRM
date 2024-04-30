import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import app

Item {
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    width: childrenRect.width
    height: childrenRect.height

    ColumnLayout{
        TextField {
            id: login_text_field
            Layout.fillWidth: true
            placeholderText : "Логин"
        }

        TextField {
            id: password_text_field
            Layout.fillWidth: true
            placeholderText : "Пароль"
            echoMode: TextInput.Password
        }

        Button{
            Layout.fillWidth: true
            text: qsTr("Вход")
            onClicked: {
                AppBackend.signIn(login_text_field.text, password_text_field.text)
            }
        }
    }
}
