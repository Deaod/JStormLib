package de.deaod.jstormlib;

public class MPQComp {
    
    private static native boolean implode(byte[] outBuffer, Integer outBufferLength, byte[] inBuffer, int inBufferLength);
    
    private static native boolean explode(byte[] outBuffer, Integer outBufferLength, byte[] inBuffer, int inBufferLength);
    
    private static native boolean compress(byte[] outBuffer, Integer outBufferLength, byte[] inBuffer, int inBufferLength, int compressionMask, int cmpType,
            int cmpLevel);
    
    private static native boolean decompress(byte[] outBuffer, Integer outBufferLength, byte[] inBuffer, int inBufferLength);
}
