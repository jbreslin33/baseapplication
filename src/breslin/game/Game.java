package breslin.game;

import com.jme3.app.SimpleApplication;
import com.jme3.material.Material;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.shape.Box;
import com.jme3.math.ColorRGBA;
import com.jme3.input.KeyInput;
import com.jme3.input.MouseInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.AnalogListener;
import com.jme3.input.controls.KeyTrigger;
import com.jme3.input.controls.MouseButtonTrigger;

//networking
import java.net.*;
import java.io.*;

/** Sample 5 - how to map keys and mousebuttons to actions */
public class Game extends SimpleApplication {

//join game
boolean sentJoinGame     = false;
boolean receivedJoinGame = false;

//network
String mServerIP;

//constructor
Game(String serverIP)
{
	mServerIP = serverIP;
}

  public static void main(String[] args) {

   if (args.length != 1) {
   		System.out.println("You need to pass in serverIP as parameter");
	    return;
   }

    Game app = new Game(args[0]);
    app.start();
  }


  protected Geometry player;
  Boolean isRunning=true;

  @Override
  public void simpleInitApp() {
    Box b = new Box(Vector3f.ZERO, 1, 1, 1);
    player = new Geometry("Player", b);
    Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
    mat.setColor("Color", ColorRGBA.Blue);
    player.setMaterial(mat);
    rootNode.attachChild(player);
    initKeys(); // load my custom keybinding

	//joinGame();

	}

void joinGame()
{
	int messageCount = 0;
    //networking
    try {

    // get a datagram socket
	DatagramSocket socket = new DatagramSocket();

	// send request
    byte[] buf = new byte[1400];

	//write to message
    buf[0] = 'j';
	messageCount++;

	//now make new buffer so that it's only as big as needed.
	byte[] realByteArray = new byte[messageCount];

	for (int i = 0; i < messageCount; i++)
	{
		realByteArray[i] = buf[i];
	}

	//create DataGramPacket
    InetAddress address = InetAddress.getByName(mServerIP);
	DatagramPacket packet = new DatagramPacket(realByteArray, realByteArray.length, address, 4445);

	//send packet to server
    socket.send(packet);

	//print out what you sent for debugging
	String s = new String(packet.getData());

    System.out.println("Data Sent:" + s);

	} catch (IOException e) {
		e.printStackTrace();
    }

}

  /** Custom Keybinding: Map named actions to inputs. */
  private void initKeys() {
    // You can map one or several inputs to one named action
    inputManager.addMapping("Pause",  new KeyTrigger(KeyInput.KEY_P));
    inputManager.addMapping("Left",   new KeyTrigger(KeyInput.KEY_K));
    inputManager.addMapping("Right",  new KeyTrigger(KeyInput.KEY_L));
    inputManager.addMapping("Rotate", new KeyTrigger(KeyInput.KEY_SPACE),
                                      new MouseButtonTrigger(MouseInput.BUTTON_LEFT));
    inputManager.addMapping("Join",   new KeyTrigger(KeyInput.KEY_J));

    // Add the names to the action listener.
    inputManager.addListener(actionListener, new String[]{"Pause"});
    inputManager.addListener(analogListener, new String[]{"Join", "Left", "Right", "Rotate"});


  }

  private ActionListener actionListener = new ActionListener() {
    public void onAction(String name, boolean keyPressed, float tpf) {
      if (name.equals("Pause") && !keyPressed) {
        isRunning = !isRunning;
      }
    }
  };

  private AnalogListener analogListener = new AnalogListener() {
    public void onAnalog(String name, float value, float tpf) {
      if (isRunning) {
        if (name.equals("Join"))
        {
        	joinGame();
        }

        if (name.equals("Rotate")) {
          player.rotate(0, value*speed, 0);
        }
        if (name.equals("Right")) {
          Vector3f v = player.getLocalTranslation();
          player.setLocalTranslation(v.x + value*speed, v.y, v.z);
        }
        if (name.equals("Left")) {
          Vector3f v = player.getLocalTranslation();
          player.setLocalTranslation(v.x - value*speed, v.y, v.z);
        }
      } else {
        System.out.println("Press P to unpause.");
      }
    }
  };
}