package de.deaod.jstormlib.data;

import lombok.Getter;
import lombok.Setter;
import de.deaod.jstormlib.MPQLocale;

public class MPQHash {
    public static final int EMPTY_BLOCK_INDEX   = 0xFFFFFFFF;
    public static final int DELETED_BLOCK_INDEX = 0xFFFFFFFE;
    
    @Getter
    @Setter
    private int             filePathHashA;
    
    @Getter
    @Setter
    private int             filePathHashB;
    
    @Getter
    @Setter
    private MPQLocale       locale;
    
    @Getter
    @Setter
    private MPQBlock        block;
}
