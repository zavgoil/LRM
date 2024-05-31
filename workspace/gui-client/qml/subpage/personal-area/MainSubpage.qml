import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import "./../../widget"

ColumnLayout{
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    height: parent.height
    width: parent.width

    Item{Layout.fillHeight:true}
    AlarmButtonWidget{}
    Item{Layout.fillHeight:true}
}

