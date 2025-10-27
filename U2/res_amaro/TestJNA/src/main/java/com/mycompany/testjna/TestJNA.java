package com.mycompany.testjna;

/**
 *
 * @author Link
 */
public class TestJNA {
    
    /*static {
        System.setProperty("jna.library.path", System.getProperty("user.dir") + "/target/classes");
    }*/

    public static void main(String[] args) {
        UseMyLib lib = UseMyLib.INSTANCE;
        
        lib.hola();
    }
}
