import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.12
Window {
    visible: true

    width: 850
    height: 600

    property var graphNumbers
    property var sizeListGraphe

    property int counterHeightChart: 20
    property int numRects: 5 // Number rects
    //    property int rectWidth: Math.floor ( ( width  - ( numRects + 1 ) * rectMargin ) / numRects)
    property int rectWidth: Math.floor ( ( width*0.9599  -  numRects   * rectMargin ) / numRects) // remove right margin
    // find best height and weight with margin between
    property int rectHeight: Math.floor( ( height*0.9 -  numRects  * rectMargin ) / numRects)
    property int rectMargin: 1 // specify the margin between each rectangle

    property bool hoveredButtonStop: true
    property bool clickeButtonStartEnable: true

    Connections{
        target: interfaceQML
        function onGraphNumberChanged(){

        }
        function onGetSizeList(_size){
            sizeListGraphe = _size
            console.log(sizeListGraphe)
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
        height: parent.height*0.9
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

    Item{
        id: sinouseNumbers
        height: parent.height
        width: parent.width*0.95
        anchors.right: parent.right
        Canvas{
            id:sinouseNumberGraph
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");
                ctx.strokeStyle = "green";
                ctx.lineWidth = 15;
                ctx.beginPath();
                ctx.moveTo(0, parent.height - 66);
                for(var i =0 ; i < sizeListGraphe; i++)
                {
                    ctx.lineTo(interfaceQML.m_graphNumber[i]  ,(interfaceQML.m_graphNumber[i+1] > sizeListGraphe ? 0 : interfaceQML.m_graphNumber[i+1]));
                }
                ctx.stroke();
            }
        }
    }

    Rectangle{
        id:buttonStop
        width: parent.width*0.1
        height: parent.height*0.09
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: parent.height*0.005
        radius: parent.width*0.01
        color: "gray"

        Text {
            id: name
            text: "Be Carefully"
            anchors.centerIn: parent
        }

        MouseArea{
            hoverEnabled: true
            anchors.fill: parent
            onReleased:  {
                clickeButtonStartEnable = true
                buttonStop.color = "gray"
                interfaceQML.inputSetSatus(false)
            }
        }
    }

    Rectangle{
        id:buttonStart
        width: parent.width*0.1
        height: parent.height*0.09
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height*0.005
        radius: parent.width*0.01

        anchors.left:buttonStop.right
        color:(clickeButtonStartEnable) ?  "green" : "gray"
        anchors.leftMargin: parent.width*0.1

        Text {
            text: "Save Life"
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            onReleased:  {
                clickeButtonStartEnable = false
                buttonStop.color = "red"
                interfaceQML.inputSetSatus(true)
            }

        }

    }
}
