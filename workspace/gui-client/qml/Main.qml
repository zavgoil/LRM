import QtQuick
import QtQuick.Window
import QtQuick.Layouts

import app
import "./widget"

import QtQuick.Controls 
import QtQuick.Controls.Material 
import QtQuick.Dialogs 

Window {
    property string defaultPage: "PersonalAreaPage.qml"
    
    id: root
    width: 1280
    height: 960
    visible: true
    title: qsTr("Danger Signal")

    function changePage(page_name)
    {
        pageLoader.source = "page/" + page_name
    }

    function showDialog(title, message, buttonListModel) {
        popupDialog.dialogTitle = title
        popupDialog.dialogMessage = message
        popupDialog.dialogButtonListModel = buttonListModel
        popupDialog.open()
    }

    function wait()
    {
        loadingPopup.open()
        
        loadingPopup.close()
    }

    Component.onCompleted: {
        changePage(root.defaultPage)
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
    }

    Dialog {
        property string dialogTitle: ""
        property string dialogMessage: ""
        property variant dialogButtonListModel: ListModel{
            ListElement{buttonText: ""; buttonCallback: function(){}}
        }
        
        id: popupDialog
        modal: true
        Material.elevation: 3
        title: dialogTitle

        anchors.centerIn: parent
        width: parent.width * 0.4

        ColumnLayout {
            anchors.fill: parent

            Item {Layout.fillHeight: true}
            Text{
                text: qsTr(popupDialog.dialogMessage)
            }
            Item {Layout.fillHeight: true}
            RowLayout{
                Layout.fillWidth: true

                Item {Layout.fillWidth: true}
                Repeater {
                    model: popupDialog.dialogButtonListModel
                    delegate: Button {
                        text: qsTr(buttonText) 
                        onClicked: {
                            popupDialog.close()
                            buttonCallback()
                        }
                    }
                }
                Item {Layout.fillWidth: true}
            }
        }
    }

    Popup {
        id: loadingPopup
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose

        background: Rectangle{
            color: "transparent"
        }

        BusyIndicator {
                id: busyIndicator
                anchors.centerIn: parent
                running: true

                width: root.width * 0.2
                height: width

                Material.foreground: Material.accent
                Material.accent: Material.Blue
        }
    }
}
