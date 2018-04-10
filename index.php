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
                echo $this->s;
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
                print '<br>';
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
        
        $test = new Neuron();
        $test->Status();
        $test->SetW0(0.3);
        $test->Status();
//        $arr = [1,1,1,1,1,1,1,1,1,1];
//        for ($i = 0; $i < count($arr); $i++) {
//            echo $arr[$i];
//        }
//        
//        $test->Status();
    
        
    
      ?>
</body>
</html>