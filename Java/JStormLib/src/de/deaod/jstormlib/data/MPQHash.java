package de.deaod.jstormlib.data;

import de.deaod.jstormlib.MPQLocale;

public class MPQHash {
    public static final int EMPTY_BLOCK_INDEX   = 0xFFFFFFFF;
    public static final int DELETED_BLOCK_INDEX = 0xFFFFFFFE;
    
    private int             filePathHashA;
    private int             filePathHashB;
    private MPQLocale       locale;
    private MPQBlock        block;
    
    public int getFilePathHashA() {
        return this.filePathHashA;
    }
    
    public void setFilePathHashA(int filePathHashA) {
        this.filePathHashA = filePathHashA;
    }
    
    public int getFilePathHashB() {
        return this.filePathHashB;
    }
    
    public void setFilePathHashB(int filePathHashB) {
        this.filePathHashB = filePathHashB;
    }
    
    public MPQLocale getLocale() {
        return this.locale;
    }
    
    public void setLocale(MPQLocale locale) {
        this.locale = locale;
    }
    
    public MPQBlock getBlock() {
        return this.block;
    }
    
    public void setBlock(MPQBlock block) {
        this.block = block;
    }
}
