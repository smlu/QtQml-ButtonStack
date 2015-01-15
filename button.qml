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
        scale: (1/3.7) / ((sourceSize.height) / parentObj.buttonSize)

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: - parentObj.buttonSize *0.05
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
        font.pointSize: Math.sqrt(buttonId.height) * ( Qt.platform.os === "osx" ? 1.3 : 1)
        wrapMode: Text.WordWrap
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: {
            if(image.source == '')
                return 0
            else
                return parentObj.buttonSize *0.20

        }
        anchors.horizontalCenter: parent.horizontalCenter
        styleColor: "#ffffff"
    }
}
