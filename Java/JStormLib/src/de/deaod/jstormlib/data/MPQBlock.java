package de.deaod.jstormlib.data;

import lombok.Getter;
import lombok.Setter;
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
    
    @Getter
    @Setter
    private int                  filePosition;
    
    @Getter
    @Setter
    private int                  compressedSize;
    
    @Getter
    @Setter
    private int                  fileSize;
    
    @Getter
    @Setter
    private MPQFileFlags      flags;
}
