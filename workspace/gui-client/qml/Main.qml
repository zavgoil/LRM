import QtQuick
import QtQuick.Window
import QtQuick.Layouts

import app
import "./widget"

Window {
    width: 640
    height: 480

    visible: true
    title: qsTr("Hello World")

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "SignUpPage.qml"
    }

    function changePage(page_name)
    {
        pageLoader.source = page_name
    }

    Component.onCompleted: AppBackend.signIn("asd", "asd")
}
