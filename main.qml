import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.12
Window {
    visible: true

    width: 850
    height: 600

    property var graphNumbers
    property var sizeListGraphe
    property var sizeListClear
    property int counterHeightChart: 20
    property int numRects: 5 // Number rects
    //    property int rectWidth: Math.floor ( ( width  - ( numRects + 1 ) * rectMargin ) / numRects)
    property int rectWidth: Math.floor ( ( width*0.9599  -  numRects   * rectMargin ) / numRects) // remove right margin
    // find best height and weight with margin between
    property int rectHeight: Math.floor( ( height*0.9 -  numRects  * rectMargin ) / numRects)
    property int rectMargin: 1 // specify the margin between each rectangle

    property bool hoveredButtonStop: true
    property bool clickeButtonStartEnable: true

    property double numberIncrease: 0.00555
    property double numberIncreaseClear: 0

    property var listValues
    property int moveToXValue:0
    property int moveToYValue : 0

    property var savePastWidth
    property var savePastWidthClear

    property bool checkClearPage: false
    property var colorStrokeStyle: "red"
    property var pastValueGraphNumber:[]
    property var pastValueMoveXNumber:[]
    property var pastValueMoveYnumber:[]
    property var pastValueNumberIncrement:[]
    property int counterSavePastNumberMoveX:0
    property int counterSavePastNumberMoveY: 0

    Connections{
        target: interfaceQML

        function onGraphNumberChanged()
        {
            //            sinouseNumberGraph.requestPaint()
            if(interfaceQML.m_status)
            {
                sinouseNumberGraph.paintingDraw()
            }
            else
            {
                sinouseNumberGraph.paintingDraw()
            }

        }
        function onClearGraphNumberChanged()
        {
            if(interfaceQML.m_clearGraphNumber[0] !== "undefined")
            {
                sinouseNumberGraph.clearDraw()
            }
        }
        function onGetSizeClear(_size)
        {
            sizeListClear = _size
        }

        function onGetSizeList(_size){
            sizeListGraphe = _size
        }
        function onStatusChanged(_status)
        {

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
        height: Math.floor(parent.height*0.9)
        width: Math.floor(parent.width*0.95)
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
        height: parent.height*0.9

        width: parent.width*0.95
        anchors.right: parent.right
        Canvas{
            id:sinouseNumberGraph
            anchors.fill: parent
            function paintingDraw()
            {
                var ctx = getContext("2d");
                ctx.strokeStyle = colorStrokeStyle
                ctx.lineWidth = 4;
                ctx.beginPath();
                ctx.moveTo(moveToXValue , moveToYValue);

                if(interfaceQML.m_status)
                {
                    colorStrokeStyle = "green"

                    for(var i =0 ; i < sizeListGraphe; i++)
                    {
                        ctx.lineTo(numberIncrease , interfaceQML.m_graphNumber[i])
                        savePastWidth  = numberIncrease
                        moveToXValue   = savePastWidth
                        moveToYValue   = interfaceQML.m_graphNumber[i]
                        numberIncrease =  numberIncrease + 1;
                        pastValueMoveXNumber[counterSavePastNumberMoveX] = moveToXValue
                        counterSavePastNumberMoveX++;
                        ctx.stroke();
                    }

                    if(numberIncrease > 807)
                    {
                        numberIncrease = 0
                        moveToXValue = 0
                        moveToYValue = 0
                        numberIncrease = 0.00555;

                    }
                }
                else
                {
                    moveToYValue = parent.height/2
                    colorStrokeStyle="red"
                    ctx.lineTo(numberIncrease , moveToYValue)
                    numberIncrease =  numberIncrease + 5

                    ctx.stroke();
                    if(numberIncrease > 807)
                    {
                        numberIncrease = 0
                    }


                }
                sinouseNumberGraph.requestPaint();
            }
            function clearDraw()
            {
                var ctx = getContext("2d");

                for(var i =0 ; i < sizeListClear; i++)
                {

                    ctx.clearRect(numberIncreaseClear, interfaceQML.m_clearGraphNumber[i], 1, 540);
                    numberIncreaseClear +=1;
                    if(numberIncreaseClear > 806)
                    {
                        numberIncreaseClear=0.00555;
                    }


                    sinouseNumberGraph.requestPaint();
                }


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
            text: "Be Carefull"
            anchors.centerIn: parent
        }

        MouseArea{
            hoverEnabled: true
            anchors.fill: parent
            onReleased:  {
                interfaceQML.inputSetSatus(false)
                clickeButtonStartEnable = true
                buttonStop.color = "gray"
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
