import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "./../../widget"

Item{
    ColumnLayout{
        anchors.centerIn: parent
        height: parent.height * 0.95
        width: parent.width * 0.6

        ContactListWidget{}

        Item{Layout.fillHeight:true}
        Button {
            text: "+ Добавить контакт"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                ContactModel.addEmptyRow()
            }
        }
    }
}


