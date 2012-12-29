<meta http-equiv="Content-type" content="text/html;charset=UTF-8">
<html>
<head>
<title>ABC AND YOU</title>

<!-- include mootools -->
<script type="text/javascript" src="/mootools/mootools-core-1.4.5-full-compat.js"></script>

<!-- include ApplicationBreslin -->
<script type="text/javascript" src="/breslin/clientside/application/application_breslin.php"></script>

<!-- include Network -->
<script type="text/javascript" src="/breslin/clientside/network/network.php"></script>

<!-- include State -->
<script type="text/javascript" src="/breslin/statemachine/state.php"></script>

<!-- include StateMachine -->
<script type="text/javascript" src="/breslin/statemachine/state_machine.php"></script>

<!-- include ApplicationGlobal -->
<script type="text/javascript" src="/breslin/clientside/application/states/application_global.php"></script>

<!-- include ApplicationInitialize -->
<script type="text/javascript" src="/breslin/clientside/application/states/application_initialize.php"></script>

<!-- include ApplicationMain -->
<script type="text/javascript" src="/breslin/clientside/application/states/application_main.php"></script>

<!-- include ApplicationPlay -->
<script type="text/javascript" src="/breslin/clientside/application/states/application_play.php"></script>

<!-- include ByteBuffer -->
<script type="text/javascript" src="/breslin/clientside/bytebuffer/byte_buffer.php"></script>

<!-- include Game -->
<script type="text/javascript" src="/breslin/clientside/game/game.php"></script>

<!-- include GameGlobal -->
<script type="text/javascript" src="/breslin/clientside/game/states/game_global.php"></script>

<!-- include GameInitialize -->
<script type="text/javascript" src="/breslin/clientside/game/states/game_initialize.php"></script>

<!-- include GamePause -->
<script type="text/javascript" src="/breslin/clientside/game/states/game_pause.php"></script>

<!-- include GamePlay -->
<script type="text/javascript" src="/breslin/clientside/game/states/game_play.php"></script>

</head>

<body bgcolor="grey">

<script language="javascript">

var mApplication;

window.addEvent('domready', function()
{
	mApplication = new ApplicationBreslin('192.168.1.100', 30004);

	//input
        document.addEvent("keydown", mApplication.keyDown);
        document.addEvent("keyup", mApplication.keyUp);

       	//main loop 
        var t=setInterval("mApplication.processUpdate()",32)
}

);

window.onresize = function(event)
{
//        GAME.mWindow = window.getSize();
}
</script>

<p id="demo">My First Paragraph</p>
<p id="demo2">My 2nd Paragraph</p>
</body>
</html>

