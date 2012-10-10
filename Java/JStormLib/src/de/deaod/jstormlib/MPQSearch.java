package de.deaod.jstormlib;

public class MPQSearch {
    
    private static native boolean findNextFile(long search, MPQFindData findFileData);
    
    private static native boolean findClose(long search);
    
    private static native boolean listFindNextFile(long search, MPQFindData findFileData);
    
    private static native boolean listFindClose(long search);
    
}
