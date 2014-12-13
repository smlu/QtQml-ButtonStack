import QtQuick 2.0

Rectangle {
    id: buttonstack    
    objectName: "buttonStack"
    property real pw : {
        return buttonSize + (Math.sqrt(Math.pow(focusMarker.width,2)+ Math.pow(focusMarker.height,2)) /2)
    }
    property real ph : parent!=null?parent.height:484
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
    property color defaultButtonColor:  "#111111"
    property color defaultOnHoverColor: "#cccccc"
    property color defaultOnClickColor: "#333333"
    property int numOfButtons: 0
    property int buttonSize:   (height/numOfButtons)+1
    property Rectangle clickedButton: Rectangle{objectName:"default"; x: -100; y: -(buttonstack.y - 100 + focusMarker.height); visible: false}
    property Rectangle hoveredButton: clickedButton


    // focused button marker
   Rectangle{
        id: focusMarker
        objectName: "__focusMarker"
        width: Math.sqrt(buttonstack.height)
        height:Math.sqrt(buttonstack.height)
        x: buttonstack.buttonSize - (width/2)
        y: buttonstack.hoveredButton.y + (buttonstack.buttonSize /2) - (height /2);
        rotation: 45
        color: buttonstack.hoveredButton.color
        visible: hoveredButton.visible
        Behavior on y {
            NumberAnimation {
                duration: 600
                easing.type: Easing.OutBack
            }
        }
    }

    function addButton(name, imageSource, buttonColor, onClickColor, onHoverColor) {

        if(typeof(buttonColor) ==='undefined' || buttonColor  === '') buttonColor  = defaultButtonColor;
        if(typeof(onClickColor)==='undefined' || onClickColor === '') onClickColor = defaultOnClickColor;
        if(typeof(onHoverColor)==='undefined' || onHoverColor === '') onHoverColor = defaultOnHoverColor;

        var sprite = button.incubateObject(layout, {                                               
                                               "id": button+name,
                                               "objectName": name,
                                               "buttonColor":  buttonColor,
                                               "onClickColor": onClickColor,
                                               "onHoverColor": onHoverColor,
                                               "label": name,
                                               "imageSource": imageSource
                                           });
        if (sprite !== null){
            numOfButtons ++;
            return true;
        }
        else{
            // Error Handling
            qmlErrors("error creating button " + name);
            console.log("Error creating button " + name );
        }

        return false;
    }

    /* Layout **/

    Column {
        id: layout
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
        spacing: 0/*
        Component.o: {
            var tmp = this.children;
            var copy = [];
            for (var i = 0; i < tmp.length; ++i)
                copy[i] = tmp[i]
           buttonList = copy;
        }*/
    }
}
