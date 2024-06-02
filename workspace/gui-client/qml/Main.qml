    import QtQuick
import QtQuick.Window
import QtQuick.Layouts

import app
import "./widget"

import QtQuick.Controls 
import QtQuick.Controls.Material 
import QtQuick.Dialogs 

Window {
    id: root
    property string defaultPage: "SignUpPage.qml"
    
    width: 1280
    height: 960
    visible: true
    title: qsTr("Danger Signal")

    function changePage(page_name)
    {
        pageLoader.source = "page/" + page_name
    }

    function showError(error_message)
    {
        showDialog("Ошибка", error_message, popupEmptyOkButton)
    }

    function showDialog(title, message, buttonListModel) {
        popupDialog.dialogTitle = title
        popupDialog.dialogMessage = message
        popupDialog.dialogButtonListModel = buttonListModel
        popupDialog.open()
    }

    Connections {
        target: AppBackend
        function onOpenLoadingPopup() {
            loadingPopup.open()
        }

        function onCloseLoadingPopup() {
            loadingPopup.close()
        }

        function onShowError(error_message) {
            showError(error_message)
        }
    }

    Component.onCompleted: {
        changePage(root.defaultPage)
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
    }

    Dialog {
        id: popupDialog
        property string dialogTitle: ""
        property string dialogMessage: ""
        property variant dialogButtonListModel: ListModel{
            ListElement{buttonText: ""; buttonCallback: function(){}}
        }
        
        modal: true
        Material.elevation: 3
        title: dialogTitle

        anchors.centerIn: parent
        width: parent.width * 0.4

        ColumnLayout {
            anchors.fill: parent
            
            Item {Layout.fillHeight: true}
            Text{
                Layout.maximumWidth: parent.width
                wrapMode: Text.WordWrap
                elide: Text.ElideRight
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

    ListModel{
        id: popupEmptyOkButton      
        ListElement{ 
            buttonText: "Ок"; 
            buttonCallback: function(){} 
        }
    }
}
