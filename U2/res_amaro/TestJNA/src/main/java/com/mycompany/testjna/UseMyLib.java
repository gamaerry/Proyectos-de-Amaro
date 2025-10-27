package com.mycompany.testjna;

import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 *
 * @author Link
 */
public interface UseMyLib extends Library {
    UseMyLib INSTANCE = Native.load(
        "practica7", 
        UseMyLib.class
    );
    
    void hola();
}
