<meta http-equiv="Content-type" content="text/html;charset=UTF-8">
<html>
<head>
<title>ABC AND YOU</title>

<!-- mootools -->
<script type="text/javascript" src="/mootools/mootools-core-1.4.5-full-compat.js"></script>

<?php
//include(getenv("DOCUMENT_ROOT") . "/web/login/check_login.php");
?>



<?php
//------------standard top of file
//include(getenv("DOCUMENT_ROOT") . "/web/game/standard_title_mootools.php");

//-----------------database
//include(getenv("DOCUMENT_ROOT") . "/src/database/db_connect.php");

//db connection
//$conn = dbConnect();


//include(getenv("DOCUMENT_ROOT") . "/web/game/standard_sessions.php");
//include(getenv("DOCUMENT_ROOT") . "/web/game/standard_games_query.php");
//question_query????
//don't need games_attempts...
//include(getenv("DOCUMENT_ROOT") . "/web/game/standard_game_includes.php");
?>

<!--
<script type="text/javascript" src="/src/game/game_quiz.php"></script>
<script type="text/javascript" src="/src/game/chooser.php"></script>
<script type="text/javascript" src="/web/game/standard_game_hud.php"></script>
-->
<!-- include application -->
<script type="text/javascript" src="/breslin/clientside/application/application_breslin.php"></script>

</head>

<body bgcolor="grey">

<script language="javascript">

var GAME;
//var mApplication;
var mHud;

window.addEvent('domready', function()
{
	mApplication = new ApplicationBreslin();

        //HUD
/*
        hud = new Hud();
        hud.mScoreNeeded.setText('<font size="2"> Needed : 1</font>');
        hud.mGameName.setText('<font size="2">DUNGEON</font>');

        //GAME
        GAME = new Chooser("Chooser");

        //set hud
        GAME.setHud(hud);

        //QUIZ
        quiz = new Quiz(1);
        GAME.mQuiz = quiz;
        quiz.mGame = GAME;

        //create questions
        GAME.createQuestions();

        //create control object
        GAME.createControlObject();

        //create doors
        GAME.createPortals();

        //KEYS
        GAME.mKeysOn = true;
        document.addEvent("keydown", GAME.keyDown);
        document.addEvent("keyup", GAME.keyUp);

        //MOUSE
        GAME.mMouseOn     = true;
        GAME.mMouseMoveOn = true;
        //GAME.mMouseDownOn = true;
*/
<?php
//include(getenv("DOCUMENT_ROOT") . "/web/game/standard_bottom.php");
?>


        //RESET GAME TO START
 //       GAME.resetGame();

        //START UPDATING
  //      var t=setInterval("GAME.update()",32)

        //brian - update score in database
   //     var t=setInterval("GAME.updateScore()",1000)

        //check if game has gone on too long
    //    var t=setInterval("GAME.checkTime()",1000)
}
);

window.onresize = function(event)
{
//        GAME.mWindow = window.getSize();
}
</script>

<p id="demo">My First Paragraph</p>
</body>
</html>

