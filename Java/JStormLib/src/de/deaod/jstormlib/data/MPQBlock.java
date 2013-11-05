package de.deaod.jstormlib.data;

import de.deaod.jstormlib.MPQFileFlags;

public class MPQBlock {
    /**
     * Dummy instance representing an invalid block element. This block is and has always been empty.
     */
    public static final MPQBlock EMPTY   = new MPQBlock();
    
    /**
     * Dummy instance representing an invalid block element. This block is currently empty, but there was a valid entry
     * before. The file has since been deleted.
     */
    public static final MPQBlock DELETED = new MPQBlock();
    
    private int                  filePosition;
    private int                  compressedSize;
    private int                  fileSize;
    private MPQFileFlags         flags;
    
    public int getFilePosition() {
        return this.filePosition;
    }
    
    public void setFilePosition(int filePosition) {
        this.filePosition = filePosition;
    }
    
    public int getCompressedSize() {
        return this.compressedSize;
    }
    
    public void setCompressedSize(int compressedSize) {
        this.compressedSize = compressedSize;
    }
    
    public int getFileSize() {
        return this.fileSize;
    }
    
    public void setFileSize(int fileSize) {
        this.fileSize = fileSize;
    }
    
    public MPQFileFlags getFlags() {
        return this.flags;
    }
    
    public void setFlags(MPQFileFlags flags) {
        this.flags = flags;
    }
    
}
