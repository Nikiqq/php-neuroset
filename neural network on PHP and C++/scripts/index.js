$(document).ready(function(){
    $('.start').on('click', function() {
        $('.solute').empty();
        $('#chart').empty(); 
        
        let vvod = {};
        
        $('.vvod').each(function(i,elem) {
             vvod[i] = $(elem).val();
        });
        
        $.ajax({
            type: "POST",
            url: "calculate.php",
            data: $("#ajax_form").serialize()
        }).done(function(result) {
            $('.solute').html("<p class='p-itog'> Выход дефаззификации:  " + result + "</p>");
            
            var Xarr = [];  // переменная, которая будет хранить координаты
            var Alfarr = [];  // переменная, которая будет хранить альфы
            
            $(".X").each(function(){
                Xarr.push($(this).val());
            });
            $(".alfa").each(function(){
                Alfarr.push($(this).val());
            });
            
            var count = Xarr.length;
            var line1=[[Xarr[0], 1], [Xarr[1], 0]]; // верхняя линия
            var line2=[[Xarr[0], 0], [Xarr[1], 1]]; // нижняя линия
            var line3=[[Xarr[0], Alfarr[0]] ]; // линия альфы
            
            if(Alfarr[0] > Alfarr[1]){
                var prom = parseFloat(Xarr[0]) + parseFloat(((Xarr[1] - Xarr[0])*(1-Alfarr[0])));
                line3.push([ prom , Alfarr[0]]);
            }
            for(var i = 2; i < count; i++){
                line1.push([Xarr[i], (i+1)%2 ]);
                line2.push([Xarr[i], (i)%2 ]);
            }
            for(var i = 0; i < count; i++){
                if(Alfarr[i] > Alfarr[i+1]) {
                    if( Alfarr[i] >= 0.5) {
                        var prom = parseFloat(Xarr[i]) + parseFloat(((Xarr[i+1] - Xarr[i])*(1-Alfarr[i])));
                        line3.push([ prom , Alfarr[i]]); 
                        if(Alfarr[i+1] > 0.5) {
                            var prom1 = (parseFloat(Xarr[i]) + parseFloat(Xarr[i+1]))/2.0;
                            line3.push([ prom1 , 0.5]);
                            var prom2 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(Alfarr[i+1]);
                            line3.push([ prom2 , Alfarr[i+1]]);
                        }
                        else {
                            var prom1 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(1-Alfarr[i+1]);
                            line3.push([ prom1 , Alfarr[i+1]]);
                        }
                    }
                    else {
                        var prom1 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(1-Alfarr[i]);
                        line3.push([ prom1 , Alfarr[i]]);
                        var prom2 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(1-Alfarr[i+1]);
                        line3.push([ prom2 , Alfarr[i+1]]); 
                    }
                }
                else {
                    if(Alfarr[i] >= 0.5){
                        var prom = parseFloat(Xarr[i]) + parseFloat(((Xarr[i+1] - Xarr[i])*(1-Alfarr[i])));
                        line3.push([ prom , Alfarr[i]]);
                        var prom1 = (parseFloat(Xarr[i]) + parseFloat(Xarr[i+1]))/2.0;
                        line3.push([ prom1 , 0.5]);
                        var prom2 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(Alfarr[i+1]);
                        line3.push([ prom2 , Alfarr[i+1]]);
                        
                    }
                    else {
                        var prom = parseFloat(Xarr[i]) + parseFloat(((Xarr[i+1] - Xarr[i])*(Alfarr[i])));
                        line3.push([ prom , Alfarr[i]]);
                        if(Alfarr[i+1] > 0.5){
                            var prom1 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(Alfarr[i+1]);
                            line3.push([ prom1 , Alfarr[i+1]]);
                        }
                        else {
                            var prom1 = parseFloat(Xarr[i]) + parseFloat(((Xarr[i+1] - Xarr[i])*(Alfarr[i+1])));
                            line3.push([ prom1 , Alfarr[i+1]]);
                            var prom2 = parseFloat(Xarr[i]) + (parseFloat(Xarr[i+1]) - parseFloat(Xarr[i]))*(1-Alfarr[i+1]);
                            line3.push([ prom2 , Alfarr[i+1]]);
                        }
                    }
                }
            }
            line3.push([ Xarr[count-1] , Alfarr[count-1]]);
            var line4 = [];
            for(var i = 0; i < count; i++){
                line4.push([Xarr[i], 0])    
            }
            
            var plot1 = $.jqplot('chart', [line1, line2, line3, line4],  {
            
                title:'График',
                
                seriesDefaults: {    
                    showMarker: false,
                    markerOptions: {
                        color: "#000000",
                        show: false,
                        style: 'filledCircle',
                        lineWidth: 1.5,
                        size: 12,
                        shadow: false
                    },
                    fill: false,
                    fillAndStroke:false,
                    drawGridlines: false,     
                    pointLabels: {
                        show: true,
                        edgeTolerance: 5
                    }
                }, 

                fillBetween: {
                    series1: [line1, line2],
                    series2: [line1, line3],
                    color: "rgba(227, 167, 111, 0.7)",
                    baseSeries: 0,
                    fill: true
                },

                seriesColors: ['#77B7C3', '#77B7C3', '#f87e7b', '#dcd1b4', '#17BDB8'],

                axesDefaults: {
                    tickRenderer: $.jqplot.CanvasAxisTickRenderer,
                    tickOptions: {
                      angle: 0
                    }
                },

                axes:{
                    xaxis:{
                        pad: 0,
                        max:Xarr[Xarr.length - 1],
                        label:'X',
                        labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
                        labelOptions: {
                            fontFamily: 'Georgia, Serif',
                            fontSize: '12pt'
                        },    
                        tickOptions:{
                            formatString:'%.2f'
                        }
                    },
                    yaxis:{
                        min: 0,
                        max: 1.2,
                        label:'a',
                        labelRenderer: $.jqplot.CanvasAxisLabelRenderer,
                        labelOptions: {
                            fontFamily: 'Georgia, Serif',
                            fontSize: '12pt'
                        },    
                        tickOptions:{
                            formatString:'%.2f'
                        }
                    }
                  },

                highlighter: {
                    show: false,
                    sizeAdjust: 7.5
                },

                cursor: {
                    show: true
                },

                grid: {
                    drawBorder: false,
                    drawGridlines: true,
                    shadow: false,
                    // background: 'rgba(0,0,0,0)'  works to make transparent.
                    background: 'white',
                    gridLineWidth: 1.5,
                    gridLineColor: 'rgb(235,235,235)'
                },    

                canvasOverlay: {
                    show: true,
                    objects: [

                        {dashedVerticalLine: {
                            name: 'wilma',
                            x: result,
                            lineWidth: 2,
                            color: 'rgb(133, 120, 24)',
                            shadow: false
                        }}
                    ]
                }
                
            });
            plot1.fillBetween.series1 = 2;
            plot1.fillBetween.series2 = 3;
            plot1.replot();
        })
    });
});