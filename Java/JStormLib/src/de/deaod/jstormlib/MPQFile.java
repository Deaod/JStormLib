package de.deaod.jstormlib;

public class MPQFile {
    
    private static native long getFileSize(long file);
    
    private static native long setFilePointer(long file, long newPosition, int moveMethod);
    
    private static native boolean readFile(long file, byte[] buffer, int bytesToRead, Integer bytesRead);
    
    private static native boolean writeFile(long file, byte[] data, int size, int compression);
    
    private static native boolean closeFile(long file);
    
    private static native boolean getFileName(long file, String name);
    
    private static native boolean getFileInfo(long file, int infoType, byte[] data, int dataMaxSize, Integer dataSize);
    
    private static native boolean setFileLocale(long file, int newLocale);
}
