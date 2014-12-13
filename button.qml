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
    property Rectangle _focusMarker: focusMarker;
    /**************************************************************/


    width:  parentObj.buttonSize
    height: parentObj.buttonSize
    color: {
        if (mArea.pressed || parentObj.selectedButton.objectName === objectName)
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
        width: parentObj.buttonSize/3.2
        height: parentObj.buttonSize/3.5
        //anchors.verticalCenterOffset: -8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source: parent.imageSource
    }


    function setFocus(){        
        parentObj.selectedButton = buttonId;
        // Marker
        _focusMarker.color = parentObj.selectedButton.color;
        _focusMarker.visible = true;
        if(parentObj.selectedButton.y )
            _focusMarker.y = parentObj.selectedButton.y + (parentObj.buttonSize /2) - (_focusMarker.height /2);
        //emit Signal
        parentObj.clicked(parentObj.selectedButton.objectName)
    }

    MouseArea {
        id:mArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onClicked: {
            parentObj.selectedButton = parent;
            // Marker
            _focusMarker.color = parentObj.selectedButton.color;
            _focusMarker.visible = true;
            _focusMarker.y = parentObj.selectedButton.y + (parentObj.buttonSize /2) - (_focusMarker.height /2);
            //emit Signal
            parentObj.clicked(parent.objectName)
        }
        hoverEnabled: true
        onEntered: {
            if(parentObj.selectedButton.objectName !== parent.objectName) {              
               // Marker
                _focusMarker.color = parent.color;
                _focusMarker.visible = true;
                _focusMarker.y = parent.y + (parentObj.buttonSize /2) - (_focusMarker.height /2);

                // emit signal
                parentObj.focusChanged(parentObj.selectedButton.objectName, parent.objectName)
            }
        }
        onExited: {
            if(parentObj.selectedButton.objectName !== parent.objectName) {
                //Marker
                _focusMarker.color = parentObj.selectedButton.color
                _focusMarker.y = parentObj.selectedButton.y + (parentObj.buttonSize /2) - (_focusMarker.height /2);

                // emit signal
                parentObj.focusChanged(parent.objectName, selectedButton.objectName)
            }
        }
    }

    Text  {
        color: {
            if (mArea.pressed || parentObj.selectedButton.objectName === parent.objectName)
                return onHoverColor
            else if(mArea.containsMouse)
                return onClickColor
            else
                return onHoverColor
        }
        text: parent.label
        font.pointSize: 10
        anchors.verticalCenterOffset: {
            if(image.source == '')
                return 0
            else
                return image.height /2 +10

        }
        wrapMode: Text.WordWrap
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        styleColor: "#ffffff"
    }
}
