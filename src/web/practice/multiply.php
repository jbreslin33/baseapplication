<!DOCTYPE html>
<html>
<head>
        <title>Practice</title>
<link rel="stylesheet" type="text/css" href="<?php getenv("DOCUMENT_ROOT")?>/css/green_block.css" />


<script>
var a = 0;
var b = 0;
var totalCorrect = 0;
var totalIncorrect = 0;
var realAnswer = 0;
var userAnswer = '';
var totalNeeded = 10;

</script>
</head>
<body>
<?php
session_start();
//db connection
include(getenv("DOCUMENT_ROOT") . "/src/database/db_connect.php");
$conn = dbConnect();

include(getenv("DOCUMENT_ROOT") . "/web/navigation/top_links_for_practice_games.php");
echo "<br>";
?>

<p>Multiply!</p>

<p id="question_paragraph">Question:</p>

<button id="but_0">0</button>
<button id="but_1">1</button>
<button id="but_2">2</button>
<button id="but_3">3</button>
<button id="but_4">4</button>
<button id="but_5">5</button>
<button id="but_6">6</button>
<button id="but_7">7</button>
<button id="but_8">8</button>
<button id="but_9">9</button>
<button id="but_ENTER" class="butters">ENTER</button>



<script>
makeQuestion();

document.getElementById("but_0").onclick=function()
{
   addToVariable("0")
};
document.getElementById("but_1").onclick=function()
{
     addToVariable("1")
};
document.getElementById("but_2").onclick=function()
{
     addToVariable("2")
};
document.getElementById("but_3").onclick=function()
{
     addToVariable("3")
};
document.getElementById("but_4").onclick=function()
{
     addToVariable("4")
};
document.getElementById("but_5").onclick=function()
{
     addToVariable("5")
};
document.getElementById("but_6").onclick=function()
{
     addToVariable("6")
};
document.getElementById("but_7").onclick=function()
{
     addToVariable("7")
};
document.getElementById("but_8").onclick=function()
{
     addToVariable("8")
};
document.getElementById("but_9").onclick=function()
{
     addToVariable("9")
};
document.getElementById("but_ENTER").onclick=function()
{
     evaluateAnswer()
};

function evaluateAnswer()
{
    if (realAnswer == userAnswer)
    {
        totalCorrect++;
        document.getElementById("correct_paragraph").innerHTML = 'Correct:' + totalCorrect;    
    }
    else
    {
        totalIncorrect++;
        document.getElementById("incorrect_paragraph").innerHTML = 'Incorrect:' + totalIncorrect;    

    }
    reset();
     
};

function reset()
{
	if (totalNeeded == totalCorrect)
	{
		alert('Way to go you answered 10 correct');
	}
	makeQuestion();
     userAnswer = '';
     document.getElementById("answer_paragraph").innerHTML = 'Answer:';
}

function addToVariable(numberToAdd)
{
    userAnswer = userAnswer + numberToAdd;
    document.getElementById("answer_paragraph").innerHTML = 'Answer:' + userAnswer;
};

function makeQuestion()
{
	a=Math.floor((Math.random()*10)+1);
	b=Math.floor((Math.random()*10)+1);
	realAnswer=a*b;
        document.getElementById('question_paragraph').innerHTML = 'Question: ' + a + ' x ' + b + ' =';    
}

</script>

<p id="answer_paragraph">Answer:</p>
<p id="correct_paragraph">Correct:</p>
<p id="incorrect_paragraph">Incorrect:</p>
</body>
</html>

