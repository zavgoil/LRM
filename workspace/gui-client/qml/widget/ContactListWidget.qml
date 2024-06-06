import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

ListView {
    id: contactListView
    Layout.fillHeight: true
    Layout.fillWidth: true
    model: ContactModel
    spacing: 10

    Component.onCompleted: AppBackend.getContacts()
    Component.onDestruction: AppBackend.setContacts()

    delegate: ItemDelegate {
        id: itemDelegate
        width: contactListView.width
        hoverEnabled: false

        RowLayout {
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.95

            ComboBox {
                id: typeComboBox
                Layout.fillWidth: true
                currentIndex: contact_type
                model: ContactModel.contactTypes
                onCurrentIndexChanged: {
                    ContactModel.editRow(index, typeComboBox.currentIndex, contactText.text)
                }
            }

            TextField {
                id: contactText
                Layout.fillWidth: true
                text: contact_data
                onTextChanged: {
                    ContactModel.editRow(index, typeComboBox.currentIndex, contactText.text)
                }
            }

            Button {
                Layout.preferredWidth: parent.width * 0.1
                text: "-"
                onClicked: ContactModel.removeRow(index)
            }
        }
    }
}
