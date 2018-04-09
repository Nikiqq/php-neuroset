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
            
            function __construct1($count) {
                for ($i = 0; $i < $count; $i++) {
                    array_push($this->w, DEFAULT_W);
                }
            }
            
            public function Status() {
                $this->s = 0;
                for ($i = 0; $i < count($this->x); $i++) {
                    $this->s += $this->w[i] * $this->x[i];
                }
                $this->s += $this->w0;
                echo $this->s;
                echo "hello";
            }
            
            public function funk() {
                $this->y = 1 / (exp(-($this->alf)*($this->S)) + 1);
            }
        }
        
        $test = new Neuron();
//        $test->Status();
    
        
    
      ?>
</body>
</html>