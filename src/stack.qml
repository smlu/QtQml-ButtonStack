import QtQuick 2.0

Rectangle {
    id: buttonstack    
    objectName: "buttonStack"
    property real pw : {
        return buttonSize + (Math.sqrt(Math.pow(focusMarker.width,2)+ Math.pow(focusMarker.height, 2)) /2)
    }
    property real ph : parent!=null ? parent.height:484
    width: pw
    height: ph
    color: "#80cccccc"
    scale: 1
    antialiasing: true
    transformOrigin: Item.Top
    clip: false
    visible: true

    // signal is sent when focus on button changes
    signal focusChanged(string fromObjName, string toObjName)

    // signal when button is clicked
    signal clicked(string objectName)

    // signal on error
    signal qmlErrors(string Error)

    // global button properties
    property var button: Qt.createComponent("qrc:/qml/button.qml")
    readonly property int __numOfButtons: layout.children.length
    property int buttonSize:   __numOfButtons ? (height / __numOfButtons) + 1 : 0
    property Rectangle checkedButton: __nullButton
    property Rectangle hoveredButton: checkedButton

    // Private properties
    readonly property Rectangle __nullButton: Rectangle{ x: -100; y: -buttonSize ; visible: false }

    // button marker
   Rectangle{
        id: focusMarker
        objectName: "__focusMarker"
        width: Math.sqrt(buttonstack.height)
        height:Math.sqrt(buttonstack.height)
        x: buttonSize - (width/2)
        y: hoveredButton.y + (buttonSize /2) - (height /2);
        rotation: 45
        color: hoveredButton.color
        visible: hoveredButton.visible

        Behavior on y {
            id: yBehavior
            NumberAnimation {
                id: yAnimation
                duration: 600
                easing.type: Easing.OutBack
            }
        }
    }

    /* Layout **/
    Column {
        id: layout
        objectName: "layout"
        width: buttonstack.width
        height: buttonstack.height
        z: 1
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        transformOrigin: Item.Center
        antialiasing: true
        scale: 1
        spacing: 0
    }
}
