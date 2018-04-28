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
                <form class="calculate-form" method="post" action="">
                   <?php 
                        for($i = 0; $i < 5; $i++){
                            print '<div class="row">
                                       <div class="unit">
                                           <label for=""><span>x<sub>'.($i+1).'</sub> =</span></label>
                                           <input required name="'.($i*2).'" type="number" step="0.1">
                                       </div>
                                       <div class="unit">
                                           <label for=""><span>&alpha;<sub>'.($i+1).'</sub> =</span></label>
                                           <input required type="number" name="'.($i*2 + 1).'" min="0" max="1" placeholder="0.0 - 1.0" step="0.01">
                                       </div>    
                                   </div>';
                        }
                   ?>
                    <div class="row">
                        <button type="submit">Рассчитать</button>
                    </div>  
                </form>
            </div>
            <div class="content">
                <div class="chart"></div>
    
      <?php
        if(isset($_POST['0']) && isset($_POST['1'])) {       
            $example = [];
            for($i = 0; $i < 10; $i++) {
                array_push($example, ($_POST["$i"]));
            }       

            define("DEFAULT_W0", 0.25);
            define("DEFAULT_W", 0.2);
            define("DEFAULT_ALF", 1);
            define("KOL_ENTER", 10);
            define("KOL_NEURON", 30);

            class Neuron  {
                private $w = []; 
                private $w0 = DEFAULT_W0;             
                private $alf = DEFAULT_ALF; 
                private $sigm;
                private $s;
                private $x = [];
                private $y;

                function __construct() {
                    for ($i = 0; $i < KOL_ENTER; $i++) {
                        array_push($this->w, DEFAULT_W);
                    }
                }

                function __construct1( $count ) {
                    for ($i = 0; $i < $count; $i++) {
                        array_push($this->w, DEFAULT_W);
                    }
                }

                public function Status() {
                    $this->s = 0;
                    for ($i = 0; $i < count($this->x); $i++) {
                        $this->s += $this->w[$i] * $this->x[$i];
                    }
                    $this->s += $this->w0;
    //                echo $this->s;
    //                echo "hello";
                }

                public function Funk() {
                    $this->y = 1 / (exp(-($this->alf)*($this->s)) + 1);
    //                echo $this->y;
                }

                public function WorkNeuron( $input ) {
                    $this->x = $input;  
                    $this->Status();
                    $this->Funk();
    //                print '<br>';
    //                echo $this->y;
                    return $this->y;
                }

                public function SetW0( $z ) {
                    $this->w0 = $z;
                } 

                public function SetX( $input ) {
                    $this->x = $input;  
                }

                public function SetW( $input ) {
                    $this->w = $input;  
                }
            }

            $first_layer = [];
            for ($i = 0; $i < KOL_NEURON; $i++) {
                $first_layer[] = new Neuron();
            }		
            $last_layer = new Neuron(KOL_NEURON);

            $handle = fopen("calculations/weights.txt", "r");
            if( $handle ) {
    //            print 'Файл успешно открыт';
                for ($i = 0; $i < KOL_NEURON; $i++) {
                    $temp_w = [];
                    $temp = fgets($handle);
                    $first_layer[$i]->SetW0($temp);
                    for ($j = 0; $j < KOL_ENTER; $j++) {
                        $temp = fgets($handle);
                        array_push($temp_w, $temp);
                    }
                    $first_layer[$i]->SetW( $temp_w );
                }
                $temp_w = [];
                $temp = fgets($handle);
                $last_layer->SetW0($temp);
                for ($i = 0; $i < KOL_NEURON; $i++) {
                    $temp = fgets($handle);
                    array_push($temp_w, $temp);
                }
                $last_layer->SetW( $temp_w );
            }
            else {
                print 'Файл не открыт';
                exit("Невозможно открыть файл");
            }
            fclose($handle);

            $x_alf_enter = [];
            $y_first_exit = [];

            for ($j = 0; $j < KOL_ENTER; $j+= 2) {
                array_push($x_alf_enter, (($example[$j]) + 10)/20);
                array_push($x_alf_enter, $example[$j+1]);
            }

            for ($j = 0; $j < KOL_NEURON; $j++) {
                array_push($y_first_exit, $first_layer[$j]->WorkNeuron( $x_alf_enter )); 
            }

            $itog = $last_layer->WorkNeuron( $y_first_exit );
            print '<br> Итоговое нормализованное значение: '. $itog .',  денормализованное: '.($itog*20 - 10);
        }
      ?>
      
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
</body>
</html>
