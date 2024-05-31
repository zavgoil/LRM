import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "./../../widget"

Item{
    ColumnLayout{
        anchors.centerIn: parent
        height: parent.height * 0.95
        width: parent.width * 0.6

        TextField {
            id: serverAddress
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            placeholderText: "Адрес сервера"
        }

        ComboBox {
            id: themeSelector
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            model: ["Светлая тема", "Тёмная тема"]
            currentIndex: 0
        }

        Switch {
            id: notificationsSwitch
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            text: "Уведомления"
            checked: true
        }

        Item{Layout.fillHeight:true}
        Button {
            Layout.alignment: Qt.AlignHCenter

            text: "Сохранить изменения"
            onClicked: {
                // Обработка сохранения настроек
                console.log("Адрес сервера:", serverAddress.text)
                console.log("Выбранная тема:", themeSelector.currentText)
                console.log("Уведомления включены:", notificationsSwitch.checked)
            }
        }
    }
}
