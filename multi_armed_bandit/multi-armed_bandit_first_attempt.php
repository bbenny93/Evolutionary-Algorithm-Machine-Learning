<?php

$epsilon = 0.1;
$steps = 100000;


function next_machine($m){
    global $epsilon;
    $best = reset(array_keys($m, max($m)));
    $rand = rand(1,100)/100;
    if($rand > $epsilon)
        return $best;
    else{
        $tmp = array($best);
        while(in_array(($rand = rand(0,9)),$tmp));
        return $rand;
    }
}    



echo "\n";
echo "epsilon: " . $epsilon . "\n";
echo "steps: " . $steps . "\n";
echo "\n";

$arms = array();

for($i=0;$i<10;$i++){
    $arms[] = rand(1,100) / 100;
}


foreach($arms as $i => $value){
    print('machine '.$i. ' with value '.$value ."\n");
}
echo "\n";
print ("the best machine is ".reset(array_keys($arms, max($arms)))."\n");

$moyenne = array();
for($i=0;$i<10;$i++){
    $moyenne[] = 50;
}

$total_reward = 0;
for($i = 0;$i<$steps;$i++){
    $next_machine = next_machine($moyenne);
    $reward = $arms[$next_machine] * rand(1,100);
    $total_reward += $reward;
    $moyenne[$next_machine] = $moyenne[$next_machine] + (1/$i)*($reward-$moyenne[$next_machine]); 
}


echo "best machine found by algorithm is:" . reset(array_keys($moyenne, max($moyenne)))." \n";
echo "with a total reward of: " .$total_reward ."\n";
echo "average of " .$total_reward/$steps . " per step\n";

















?>