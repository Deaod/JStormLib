package de.deaod.jstormlib.data;

import de.deaod.jstormlib.MPQLocale;
import lombok.Getter;

public class MPQFindData {
    @Getter
    private String fileName;
    
    @Getter
    private String plainName;
    
    @Getter
    private int    hashIndex;
    
    @Getter
    private int    blockIndex;
    
    @Getter
    private int    fileSize;
    
    @Getter
    private int    fileFlags;
    
    @Getter
    private int    compSize;
    
    private int    fileTimeLo;
    private int    fileTimeHi;
    
    private int    locale;
    
    public long getFileTime() {
        return (((long) this.fileTimeHi << 32L) & 0xFFFFFFFF00000000L) | this.fileTimeLo;
    }
    
    public MPQLocale getLocale() {
        return MPQLocale.fromInteger(this.locale);
    }
}
