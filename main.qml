import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.12
Window {
    visible: true
    width: 800
    height: 500
    property var graphNumbers

    property int counterHeightChart: 20
    property int numRects: 5 // Number rects
    //    property int rectWidth: Math.floor ( ( width  - ( numRects + 1 ) * rectMargin ) / numRects)
    property int rectWidth: Math.floor ( ( width  -  numRects   * rectMargin ) / numRects) // remove right margin
    // find best height and weight with margin between
    property int rectHeight: Math.floor( ( height -  numRects  * rectMargin ) / numRects)
    property int rectMargin: 1 // specify the margin between each rectangle

    Connections{
        target: interfaceQML
        function onGraphNumberChanged(_list){
            console.log("omad")
        }
    }

    Label{
        id:number1
        text: "20"
        font.pixelSize: parent.width*0.03
        color: "green"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: parent.height*0.1
    }
    Label{
        id:number2
        text: "15"
        font.pixelSize: parent.width*0.03
        color: "green"
        anchors.left: parent.left
        anchors.top: number1.bottom
        anchors.topMargin: parent.height*0.1

    }
    Label{
        id:number3
        text: "10"
        font.pixelSize: parent.width*0.03
        color: "green"
        anchors.left: parent.left
        anchors.top: number2.bottom
        anchors.topMargin: parent.height*0.15
    }

    Label{
        id:number4
        text: "5"
        font.pixelSize: parent.width*0.03
        color: "green"
        anchors.left: parent.left
        anchors.top: number3.bottom
        anchors.topMargin: parent.height*0.15
    }

    Label{
        id:number5
        text: "0"
        font.pixelSize: parent.width*0.03
        color: "red"
        anchors.left: parent.left
        anchors.top: number4.bottom
        anchors.topMargin: parent.height*0.12
    }

    Rectangle {
        id: rect
        height: parent.height
        width: parent.width*0.95
        anchors.right: parent.right
        Canvas {
            id: canvas
            anchors.fill: parent

            onPaint: {
                var ctx = getContext("2d");
                ctx.fillStyle = "gray";

                for (var i = 0; i < numRects; i++)
                {
                    for (var j = 0; j < numRects; j++)
                    {
                        var x = i * (rectWidth + rectMargin)
                        var y = j * (rectHeight + rectMargin) + rectMargin
                        ctx.fillRect(x, y, rectWidth, rectHeight )
                    }
                }

                ctx.strokeStyle = "red";
                ctx.lineWidth = 6;
                ctx.beginPath();
                ctx.moveTo(0, parent.height -3);
                ctx.lineTo(parent.width, parent.height -3 );
                ctx.stroke();
            }
        }
    }

//    Item{
//        id: sinouseNumbers
//        height: parent.height
//        width: parent.width*0.95
//        anchors.right: parent.right

//        Canvas{
//            anchors.fill: parent
//            onPaint: {
//                var ctx = getContext("2d");
//                ctx.strokeStyle = "green";
//                ctx.lineWidth = 5;
//                ctx.beginPath();
//                ctx.moveTo(0, parent.height - 50);
//                for(var i = 0 ; i < 12 ; )
//                {
////                    ctx.lineTo(i , (parent.height - j));
//                }
//                ctx.stroke();
//            }
//        }
//    }
}
