import QtQuick 2.3

Rectangle  {
    id: rootItem
    /* Button properties */
    property alias text: textItem.text
    property string iconSource;
    property color backgroundColor;
    property color pressColor;
    property color hoverColor;
    property bool checked: stackObj.checkedButton === rootItem;
    property Rectangle stackObj: null;

    signal pressed();
    signal released()
    signal clicked();

    function click() {
        mArea.clicked(Qt.MouseEvent);
    }

    /**************************************************************/

    width:  stackObj.buttonSize
    height: stackObj.buttonSize

    border  { width: 0 }
    smooth: true
    radius: 0
    antialiasing: true
    border.color: "#000000"
    color: {
        if (mArea.pressed || stackObj.checkedButton === rootItem){
            return pressColor
        }
        else if(mArea.containsMouse){
            return hoverColor
        }
        else{
            return backgroundColor
        }
    }

    Component.onDestruction: {
        if(stackObj) {
            if(stackObj.checkedButton === rootItem) {
                stackObj.checkedButton = stackObj.__nullButton
            }

            if(stackObj.hoveredButton === rootItem) {
                stackObj.hoveredButton = stackObj.checkedButton;
            }
        }
    }

    Image {
        id: image
        antialiasing: true     
        scale: (1 / 3.7) / (sourceSize.height / stackObj.buttonSize)

        anchors.verticalCenter: rootItem.verticalCenter
        anchors.verticalCenterOffset: - stackObj.buttonSize * 0.05
        anchors.horizontalCenter: rootItem.horizontalCenter
        source: parent.iconSource
    }

    MouseArea {
        id: mArea
        anchors.fill: rootItem
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        //focus: fals

        onPressed: {
            rootItem.pressed();
        }

        onReleased: {
            rootItem.released();
        }

        onClicked: {
            stackObj.checkedButton = rootItem;
            rootItem.forceActiveFocus();
            rootItem.clicked();
        }

        onEntered: {
            if(stackObj.checkedButton !== rootItem) {
                stackObj.hoveredButton = rootItem;
                rootItem.forceActiveFocus();
            }
        }

        onExited: {
            if(stackObj.checkedButton !== rootItem) {
                stackObj.hoveredButton = stackObj.checkedButton;
                stackObj.checkedButton.forceActiveFocus();
                if(stackObj.checkedButton === stackObj.__nullButton) {
                    stackObj.forceActiveFocus();
                }
            }
        }
    }

    Text  {
        id: textItem
        antialiasing: true
        color: {
            if (mArea.pressed || stackObj.checkedButton === rootItem) {
                return "#cccccc"
            }
            else if(mArea.containsMouse) {
                return "#333333"
            }
            else {
                return "#cccccc"
            }
        }

        font.pointSize: Math.sqrt(rootItem.height) * ( Qt.platform.os === "osx" ? 1.3 : 1)
        wrapMode: Text.WordWrap
        anchors.verticalCenter: rootItem.verticalCenter
        anchors.verticalCenterOffset: {
            if(image.source == '') {
                return 0
            }
            else {
                return stackObj.buttonSize * 0.20
            }
        }
        anchors.horizontalCenter: rootItem.horizontalCenter
        styleColor: "#ffffff"
    }
}
