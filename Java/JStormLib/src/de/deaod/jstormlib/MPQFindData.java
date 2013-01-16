package de.deaod.jstormlib;

public class MPQFindData {
    private String fileName;
    private String plainName;
    private int    hashIndex;
    private int    blockIndex;
    private int    fileSize;
    private int    fileFlags;
    private int    compSize;
    private int    fileTimeLo;
    private int    fileTimeHi;
    private int    locale;
    
    public String getFileName() {
        return this.fileName;
    }
    
    public String getPlainName() {
        return this.plainName;
    }
    
    public int getHashIndex() {
        return this.hashIndex;
    }
    
    public int getBlockIndex() {
        return this.blockIndex;
    }
    
    public int getFileSize() {
        return this.fileSize;
    }
    
    public int getFileFlags() {
        return this.fileFlags;
    }
    
    public int getCompSize() {
        return this.compSize;
    }
    
    public long getFileTime() {
        return (((long) this.fileTimeHi << 32L) & 0xFFFFFFFF00000000L) | this.fileTimeLo;
    }
    
    public int getLocale() {
        return this.locale;
    }
}
