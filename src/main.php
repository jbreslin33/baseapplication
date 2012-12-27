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

</head>

<body bgcolor="grey">

<script language="javascript">

var mApplication;

window.addEvent('domready', function()
{
	mApplication = new ApplicationBreslin();
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

