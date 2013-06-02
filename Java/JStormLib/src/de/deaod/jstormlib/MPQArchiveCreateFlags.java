package de.deaod.jstormlib;

import java.util.EnumSet;
import java.util.Iterator;

public class MPQArchiveCreateFlags {
    
    public enum Version {
        /**
         * Creates an MPQ version 1.0 (up to 4 GB). This is the default value.
         */
        VERSION_1(0x00000000),
        /**
         * Creates an MPQ version 2.0 (supports MPQ of size greater than 4 GB).
         */
        VERSION_2(0x00010000),
        /**
         * Creates an MPQ version 3.0 (introduced in WoW-Cataclysm Beta).
         */
        VERSION_3(0x00020000),
        /**
         * Creates an MPQ version 4.0 (used in WoW-Cataclysm).
         */
        VERSION_4(0x00030000);
        
        private int value;
        
        public int getValue() {
            return this.value;
        }
        
        private Version(int value) {
            this.value = value;
        }
    }
    
    public enum MPQCreateFlag {
        /**
         * When creating new MPQ, the (attributes) file will be added to it. The (attributes) file contains additional
         * file information, such as file time, CRC32 checksum and MD5 hash.
         */
        CREATE_ATTRIBUTES(0x00000001);
        
        private int value;
        
        public int getValue() {
            return this.value;
        }
        
        private MPQCreateFlag(int value) {
            this.value = value;
        }
    }
    
    private Version                version     = Version.VERSION_1;
    private EnumSet<MPQCreateFlag> createFlags = EnumSet.noneOf(MPQCreateFlag.class);
    
    public void setVersion(Version version) {
        this.version = version;
    }
    
    public void setCreateFlags(EnumSet<MPQCreateFlag> createFlags) {
        this.createFlags = createFlags;
    }
    
    public int getFlags() {
        int result = 0;
        result |= this.version.getValue();
        Iterator<MPQCreateFlag> it = this.createFlags.iterator();
        while (it.hasNext()) {
            MPQCreateFlag flag = it.next();
            result |= flag.getValue();
        }
        return result;
    }
}
