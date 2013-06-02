package de.deaod.jstormlib;

import java.util.EnumSet;

public class MPQFileFlags {
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
    
    public static MPQFileFlags fromInteger(int value) {
        MPQFileFlags result = new MPQFileFlags();
        for (Flag f : Flag.values()) {
            if ((value & f.getValue()) != 0) {
                result.flags.add(f);
            }
        }
        
        for (Compression c : Compression.values()) {
            if (c != Compression.NONE && (value & c.getValue()) != 0) {
                result.compression = c;
                break;
            }
        }
        
        for (Encryption e : Encryption.values()) {
            if (e != Encryption.NONE && (value & e.getValue()) != 0) {
                result.encryption = e;
                break;
            }
        }
        return result;
    }
    
}
