package de.deaod.jstormlib;

import java.util.EnumSet;

/**
 * Container class for sets of flags for use when opening an MPQ archive.
 * 
 * @author Deaod <deaod@deaod.de>
 * 
 */
public class MPQArchiveOpenFlags {
    
    /**
     * Enum for different ways to open MPQ archives.
     * 
     * @author Deaod <deaod@deaod.de>
     * 
     */
    public enum BaseProvider {
        /**
         * The MPQ is a local file. This is the default value.
         */
        FILE(0x0),
        /**
         * The MPQ is a local file. Stormlib will attempt to map the file into memory. This speeds up the MPQ operations
         * (reading, verifying), but has size and operating system limitations.
         */
        MAP(0x1),
        /**
         * The MPQ is on a web server available via HTTP protocol. The server must support random access. Only supported
         * in Windows.
         */
        HTTP(0x2);
        
        private int value;
        
        public int getValue() {
            return this.value;
        }
        
        private BaseProvider(int value) {
            this.value = value;
        }
    }
    
    /**
     * Enum for different types of MPQs.
     * 
     * @author Deaod <deaod@deaod.de>
     */
    public enum StreamProvider {
        /**
         * The MPQ is a plain linear file. This is the default value.
         */
        LINEAR(0x00),
        /**
         * The MPQ is stored in a partial file. Partial files were used by trial version of World of Warcraft (build
         * 10958 - 11685).
         */
        PARTIAL(0x10),
        /**
         * The MPQ is encrypted (.MPQE). Encrypted MPQs are used by Starcraft II and Diablo III installers. StormLib
         * attempts to use all known keys. If no key can be used for decrypting the MPQ, the open operation fails.
         */
        ENCRYPTED(0x20),
        /**
         * The MPQ divided to multiple blocks and multiple files. Size of one block is 0x4000 bytes, maximum number of
         * blocks per file is 0x2000. Each block is followed by MD5 hash in plain ANSI text form. If the total number of
         * blocks in the archive is greater than 0x2000, then the archive is split into multiple files. These files have
         * decimal numeric extensions in ascending order (.MPQ.0, .MPQ.1, .MPQ.2 and so on).
         */
        BLOCK4(0x30);
        
        private int value;
        
        public int getValue() {
            return this.value;
        }
        
        private StreamProvider(int value) {
            this.value = value;
        }
    }
    
    /**
     * Enum for flags to use when opening an MPQ.
     * 
     * @author Deaod <deaod@deaod.de>
     */
    public enum StreamFlag {
        /**
         * This flag causes the file to be open read-only. This flag is automatically set for partial and encrypted
         * MPQs, and also for all MPQs that are not opened using BaseProvider.FILE.
         */
        READ_ONLY(0x00000100),
        /**
         * This flag causes the writable MPQ being open for write share. Use with caution. If two applications write to
         * an open MPQ simultaneously, the MPQ data can get corrupted.
         */
        WRITE_SHARE(0x00000200),
        /**
         * This flag tells the file stream handler to respect a file bitmap. File bitmap is used by MPQs whose file
         * blocks are downloaded on demand by the game.
         */
        USE_BITMAP(0x00000400),
        /**
         * Don't read the internal listfile.
         */
        NO_LISTFILE(0x00010000),
        /**
         * Don't open the "(attributes)" file.
         */
        NO_ATTRIBUTES(0x00020000),
        /**
         * Do not search the header at 0x200 byte offsets.
         */
        NO_HEADER_SEARCH(0x00040000),
        /**
         * Forces the MPQ to be open as MPQ format 1.0, ignoring "wFormatVersion" variable in the header. Useful for
         * opening "protected" WarCraft III maps.
         */
        FORCE_MPQ_V1(0x00080000),
        /**
         * Reading any file from the MPQ will check the CRC-hash of each file sector until the archive is closed.
         */
        CHECK_SECTOR_CRC(0x00100000);
        
        private int value;
        
        int getValue() {
            return this.value;
        }
        
        private StreamFlag(int value) {
            this.value = value;
        }
    }
    
    private BaseProvider        baseProvider   = BaseProvider.FILE;
    private StreamProvider      streamProvider = StreamProvider.LINEAR;
    private EnumSet<StreamFlag> streamFlags    = EnumSet.noneOf(StreamFlag.class);
    
    /**
     * Changes the way the MPQ is loaded into memory.
     * 
     * @param baseProvider the new way to load the MPQ into memory
     */
    public void setBaseProvider(BaseProvider baseProvider) {
        this.baseProvider = baseProvider;
    }
    
    /**
     * Changes the type of MPQ thats expected to be opened.
     * 
     * @param streamProvider the new type of MPQ expected
     */
    public void setStreamProvider(StreamProvider streamProvider) {
        this.streamProvider = streamProvider;
    }
    
    /**
     * Changes the flags to use when opening an MPQ.
     * 
     * @param streamFlags the new flags
     */
    public void setOpenFlags(StreamFlag... streamFlags) {
        for (StreamFlag flag : streamFlags) {
            this.streamFlags.add(flag);
        }
    }
    
    int getFlags() {
        int result = 0;
        result |= this.baseProvider.getValue();
        result |= this.streamProvider.getValue();
        for (StreamFlag streamFlag : this.streamFlags) {
            result |= streamFlag.getValue();
        }
        return result;
    }
}
