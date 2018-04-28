<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lessons</title>
    <link rel="stylesheet" href="styles/style.css">
    <link href="https://fonts.googleapis.com/css?family=Oswald" rel="stylesheet">
    <link rel="stylesheet" type="text/css" href="scripts/plot/jquery.jqplot.css" />
    <link href="https://use.fontawesome.com/releases/v5.0.8/css/all.css" rel="stylesheet">
</head>
<body>
    <div class="wrapper">
        <div class="header">
            <h1>Нейросетевой дефаззификатор</h1>
            <p>Создан при поддержке кафедры ИКТ РХТУ им. Д. И. Менделеева</p>
        </div>
        <div class="main">
            <div class="sidebar">
                <div class="menu-title">
                    <i class="fas fa-cog"></i>
                    <span>Параметры</span>
                </div>
                <div class="description">
                    <p>
                        Задайте координаты вершин (x) дефаззификации и соответствующие степени принадлежности (&alpha;).
                    </p>        
                </div>                      
                <form class="calculate-form" method="post" action="" id="ajax_form">
                   <?php 
                        for($i = 0; $i < 5; $i++){
                            print '<div class="row">
                                       <div class="unit">
                                           <label for=""><span>x<sub>'.($i+1).'</sub> =</span></label>
                                           <input class="vvod X" required name="'.($i*2).'" type="number" step="0.1">
                                       </div>
                                       <div class="unit">
                                           <label for=""><span>&alpha;<sub>'.($i+1).'</sub> =</span></label>
                                           <input class="vvod alfa" required type="number" name="'.($i*2 + 1).'" min="0" max="1" placeholder="0.0 - 1.0" step="0.01">
                                       </div>    
                                   </div>';
                        }
                   ?>
                    <div class="row">
                        <input class="start" type="button" value="Рассчитать">
                    </div>  
                </form>
            </div>
            <div class="content">
                <div class="solute"></div>
                <div id="chart"></div>
            </div>
        </div>
    </div>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jqPlot/1.0.9/jquery.jqplot.min.js"></script>  
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.canvasTextRenderer.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.canvasAxisLabelRenderer.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.canvasAxisTickRenderer.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.canvasOverlay.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.highlighter.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.cursor.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.categoryAxisRenderer.js"></script>
    <script type="text/javascript" src="scripts/plot/plugins/jqplot.dateAxisRenderer.js"></script> 
    <script type="text/javascript" src="scripts/index.js"></script>   
</body>
</html>
