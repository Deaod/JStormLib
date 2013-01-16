package de.deaod.jstormlib;

import java.util.EnumSet;

public class MPQAddFileFlags {
    public enum Compression {
        NONE(0x000),
        IMPLODE(0x100),
        COMPRESS(0x200);
        
        private Compression(int value) {
            this.value = value;
        }
        
        private int value;
        
        int getValue() {
            return this.value;
        }
    }
    
    public enum Encryption {
        NONE(0x00000000),
        ENCRYPTED(0x00010000),
        ENCRYPTED_FIX_KEY(0x00030000),
        SINGLE_UNIT(0x01000000);
        
        private Encryption(int value) {
            this.value = value;
        }
        
        private int value;
        
        int getValue() {
            return this.value;
        }
    }
    
    public enum Flag {
        NONE(0x00000000),
        DELTE_MARKER(0x02000000),
        REPLACE_EXISTING(0x08000000);
        
        private Flag(int value) {
            this.value = value;
        }
        
        private int value;
        
        int getValue() {
            return this.value;
        }
    }
    
    private Compression   compression = Compression.NONE;
    private Encryption    encryption  = Encryption.NONE;
    private EnumSet<Flag> flags       = EnumSet.noneOf(Flag.class);
    
    public int getFlags() {
        int result = 0;
        result |= this.compression.getValue();
        result |= this.encryption.getValue();
        for (Flag f : this.flags) {
            result |= f.getValue();
        }
        return result;
    }
    
}
