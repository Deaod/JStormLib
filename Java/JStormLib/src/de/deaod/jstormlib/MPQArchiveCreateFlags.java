package de.deaod.jstormlib;

/**
 * Flags for use when creating a new MPQ archive.
 * 
 * @author Deaod <deaod@deaod.de>
 */
public class MPQArchiveCreateFlags {
    
    /**
     * Version of a new MPQ archive.
     * 
     * @author Deaod <deaod@deaod.de>
     * 
     */
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
         * Creates an MPQ version 4.0 (used in WoW-Cataclysm, SC2, D3, ...).
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
    
    /**
     * Additional flags for creating an MPQ archive.
     * 
     * @author Deaod <deaod@deaod.de>
     * 
     */
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
    
    private Version         version     = Version.VERSION_1;
    private MPQCreateFlag[] createFlags = new MPQCreateFlag[0];
    
    /**
     * Changes the version to use when creating a new archive using these flags.
     * 
     * @param version the new version to use
     */
    public void setVersion(Version version) {
        this.version = version;
    }
    
    /**
     * Changes the additional flags to use when creating a new MPQ archive.
     * 
     * @param createFlags the new additional flags
     */
    public void setCreateFlags(MPQCreateFlag... createFlags) {
        this.createFlags = createFlags;
    }
    
    /**
     * Returns an integer representation of the options to use when creating a new MPQ archive.
     * 
     * @return an integer representation of the options to use when creating a new MPQ archive
     */
    public int getFlags() {
        int result = 0;
        result |= this.version.getValue();
        for (MPQCreateFlag flag : this.createFlags) {
            result |= flag.getValue();
        }
        return result;
    }
}
