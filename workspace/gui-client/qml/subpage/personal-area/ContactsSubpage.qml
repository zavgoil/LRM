import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "./../../widget"

Item{
    ColumnLayout{
        anchors.centerIn: parent
        height: parent.height * 0.95
        width: parent.width * 0.6

        ListModel {
            id: contactsModel
            ListElement { type: "Telegram"; details: "@username" }
            ListElement { type: "Email"; details: "example@example.com" }
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: contactsModel
            spacing: 10

            delegate: ItemDelegate {
                id: itemDelegate
                width: parent.width
                hoverEnabled: false

                RowLayout {
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width * 0.95

                    ComboBox {
                        id: typeComboBox
                        Layout.fillWidth: true

                        model: ["Telegram", "Внутреннее приложение", "Email"]
                        currentIndex: model.type === "Telegram" ? 0 : model.type === "Внутреннее приложение" ? 1 : 2
                        onCurrentIndexChanged: {
                        }
                    }

                    TextField {
                        Layout.fillWidth: true
                        text: model.details
                        onTextChanged: {
                        }
                    }

                    Button {
                        Layout.preferredWidth: parent.width * 0.1
                        text: "-"
                        onClicked: contactsModel.remove(index)
                    }
                }
            }
        }

        Item{Layout.fillHeight:true}
        Button {
            text: "+ Добавить контакт"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                contactsModel.append({type: "Telegram", details: ""})
            }
        }
    }
}


