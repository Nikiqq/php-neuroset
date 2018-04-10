<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Neuroset</title>
</head>
<body>
    <h1>Нейросеть деффазификации</h1> 
    
      <?php
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
        
//        $test = new Neuron();
//        $test->Status();
//        $test->SetW0(0.3);
//        $test->Status();
//        $arr = [1,1,1,1,1,1,1,1,1,1];
//        for ($i = 0; $i < count($arr); $i++) {
//            echo $arr[$i];
//        }
//        
//        $test->Status();
    
        $first_layer = [];
        for ($i = 0; $i < KOL_NEURON; $i++) {
            $first_layer[] = new Neuron();
        }		
		$last_layer = new Neuron(KOL_NEURON);
                
        $handle = fopen("calculations/weights.txt", "r");
        if( $handle ) {
            print 'Файл успешно открыт';
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
    
        $example = [-7.7, 0, -2.4, 0.9, 1, 0.2, 3.7, 0.6, 8.5, 0];
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
      ?>
</body>
</html>