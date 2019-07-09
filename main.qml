import QtQuick 2.13
import QtQuick.Controls 2.13

ApplicationWindow {
    objectName: "TheApplicationWindow"
    visible: true
    width: 320
    height: 200
    title: qsTr("Scroll")
    LoggingRectangle{
        id: loggingRectangle
        objectName: "loggingRectangle"
        anchors.fill: parent
        bordercolor: "green"
    }

}
