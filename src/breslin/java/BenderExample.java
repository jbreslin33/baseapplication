/*
 * BenderExample.java
 *
 * Created on September 26, 2003, 4:49 PM
 */

/**
 *
 * @author  cyphre
 */

import java.io.*;

public class BenderExample {
    
    public BenderExample() {
    }
    
    public static char readChars(){
        char c=' ';
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("1-TurnOn 2-TurnOff 3-GoToActivity 4-Walk 5-Run 6-Talk 7-RequestTurnOff");
        System.out.println("Enter your choice:");
        //        do {
        try {
            c = (char) br.read( );
            return c;
        } catch (IOException e) {
            System.out.println("IO Exception on Buffered Read");
        };
        //        } while (c != '.');
        return c;
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Fsm benderFsm = new Fsm();
        State[] st = new State[3];
        
        for(int i = 0;i < st.length;++i){
            st[i] = new State();
        }
        
        st[0].setName("Idle");
        st[0].addAction(State.ON_EXIT,"TurnOn", null, 1);
        st[0].addAction(State.ON_EVENT, "TurnOff", "TurnOff", 2);
        st[0].addTransition("TurnOn", st[1]);
        
        st[1].setName("TurnedOn");
        st[1].addAction(State.ON_ENTER, "TurnOn", null, 3);
        st[1].addTransition("TurnOff", st[0]);
        st[1].addTransition("GoToActivity", st[2]);
        
        st[2].setName("Activity");
        st[2].addAction(State.ON_EVENT, "Walk", "Walk", 4);
        st[2].addAction(State.ON_EVENT, "Run", "Run", 5);
        st[2].addAction(State.ON_EVENT, "Talk", "Talk", 6);
        st[2].addTransition("Walk", st[2]);
        st[2].addTransition("Run", st[2]);
        st[2].addTransition("Talk", st[2]);
        st[2].addTransition("RequestTurnOff", st[1]);
        
        benderFsm.addStates(st, 0);
        while(true){
            int e = readChars();
            switch (e){
                case '1':
                    benderFsm.outEvent("TurnOn");
                    break;
                case '2':
                    benderFsm.outEvent("TurnOff");
                    break;
                case '3':
                    benderFsm.outEvent("GoToActivity");
                    break;
                case '4':
                    benderFsm.outEvent("Walk");
                    break;
                case '5':
                    benderFsm.outEvent("Run");
                    break;
                case '6':
                    benderFsm.outEvent("Talk");
                    break;
                case '7':
                    benderFsm.outEvent("RequestTurnOff");
                    break;
                default:
                    benderFsm.event = "Unknown event";
                    break;
            }
            System.out.println("Status: " + benderFsm.event);
            System.out.println("Response: " + benderFsm.response);
            System.out.println("Current state: " + benderFsm.currState.name);
        }
    }
    
}
