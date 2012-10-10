package de.deaod.jstormlib;

public class MPQArchive {
    
    private static native boolean openArchive(String name, int priority, int flags, Long mpq);
    
    private static native boolean createArchive(String name, int flags, int maxFileCount, Long mpq);
    
    private static native int addListFile(long mpq, String name);
    
    private static native void setLocale(int locale);
    
    private static native int getLocale();
    
    private static native boolean flushArchive(long mpq);
    
    private static native boolean closeArchive(long mpq);
    
    private static native boolean setMaxFileCount(long mpq, int maxFileCount);
    
    private static native boolean compactArchive(long mpq, String listFile, boolean reserved);
    
    // private static native boolean setCompactCallback(long mpq, long callbackFunction, long data);
    
    private static native boolean openPatchArchive(long mpq, String name, String patchPathPrefix, int flags);
    
    private static native boolean isPatchedArchive(long mpq);
    
    private static native boolean addFileEx(long mpq, String fileName, String archivedName, int flags, int compression, int compressionNext);
    
    // private static native boolean setAddFileCallback(long mpq, long callbackFunction, long data);
    
    private static native boolean createFile(long mpq, String archivedName, long fileTime, int fileSize, int locale, int flags, Long file);
    
    private static native boolean openFile(long mpq, String name, int scope, Long file);
    
    private static native boolean hasFile(long mpq, String name);
    
    private static native boolean renameFile(long mpq, String oldFileName, String newFileName);
    
    private static native boolean removeFile(long mpq, String fileName, int searchScope);
    
    private static native boolean getArchiveInfo(long mpq, int infoType, byte[] data, int dataMaxSize, Integer dataSize);
    
    private static native boolean verifyFile(long mpq, String fileName, int flags);
    
    private static native int verifyArchive(long mpq);
    
    private static native boolean extractFile(long mpq, String toExtract, String extracted, int searchScope);
    
    private static native long findFirstFile(long mpq, String mask, MPQFindData fileFindData, String listFile);
    
    private static native long listFindFirstFile(long mpq, String listFile, String mask, MPQFindData fileFindData);
    
    public MPQArchive(String file) {
        
    }
}
