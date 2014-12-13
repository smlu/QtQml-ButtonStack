import QtQuick 2.0

Rectangle  {
id: buttonId
    /* to change button rename these vars */ 
    property string label;
    property string imageSource;
    property color buttonColor;
    property color onClickColor;
    property color onHoverColor;
    property Rectangle parentObj: buttonstack;
    property Rectangle clickedButton;
    /**************************************************************/


    width:  parentObj.buttonSize
    height: parentObj.buttonSize
    color: {
        if (mArea.pressed || parentObj.clickedButton.objectName === objectName)
            return onClickColor
        else if(mArea.containsMouse)
            return onHoverColor
        else
            return buttonColor
    }
    border  { width: 0 }
    smooth: true
    radius: 0    
    antialiasing: true
    border.color: "#000000"

    Image {
        id: image
        antialiasing: true
        width: parentObj.buttonSize/2.8
        height: parentObj.buttonSize/2.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -5
        anchors.horizontalCenter: parent.horizontalCenter
        source: parent.imageSource
    }


    function setFocus(){
        var previousBtn = parentObj.hoveredButton.objectName;
        parentObj.clickedButton= buttonId;
        parentObj.hoveredButton = buttonId;
        parentObj.focusChanged(previousBtn, parentObj.hoveredButton.objectName)
        parentObj.clicked(parentObj.clickedButton.objectName)
    }

    MouseArea {
        id:mArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onClicked: {
            parentObj.clickedButton = buttonId;

            //emit Signal            
            parentObj.clicked(buttonId.objectName)
        }
        hoverEnabled: true
        onEntered: {
            if(parentObj.clickedButton.objectName !== parent.objectName) {
                parentObj.hoveredButton = buttonId;

                // emit signal
                parentObj.focusChanged(parentObj.clickedButton.objectName, buttonId.objectName)
            }
        }
        onExited: {
            if(parentObj.clickedButton.objectName !== parent.objectName) {
                parentObj.hoveredButton = parentObj.clickedButton;

                // emit signal
                parentObj.focusChanged(buttonId.objectName, parentObj.clickedButton.objectName)
            }
        }
    }

    Text  {
        antialiasing: true
        color: {
            if (mArea.pressed || parentObj.clickedButton.objectName === parent.objectName)
                return "#cccccc"
            else if(mArea.containsMouse)
                return "#333333"
            else
                return "#cccccc"
        }
        text: parent.label
        font.pointSize: Math.ceil(Math.sqrt(buttonId.height)) +2
        wrapMode: Text.WordWrap
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: {
            if(image.source == '')
                return 0
            else
                return Math.ceil(image.height /2) + Math.ceil(Math.sqrt(buttonId.height))

        }
        anchors.horizontalCenter: parent.horizontalCenter
        styleColor: "#ffffff"
    }
}
