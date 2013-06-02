package de.deaod.jstormlib;

import java.util.EnumSet;

public class MPQArchiveOpenFlags {
    
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
        ENCRYPTED(0x20);
        
        private int value;
        
        public int getValue() {
            return this.value;
        }
        
        private StreamProvider(int value) {
            this.value = value;
        }
    }
    
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
         * Don't read the internal listfile.
         */
        NO_LISTFILE(0x00010000),
        /**
         * Don't open the "(attributes)" file.
         */
        NO_ATTRIBUTES(0x00020000),
        /**
         * Forces the MPQ to be open as MPQ format 1.0, ignoring "wFormatVersion" variable in the header. Useful for
         * opening "protected" WarCraft III maps.
         */
        FORCE_MPQ_V1(0x00040000),
        /**
         * Reading any file from the MPQ will check the CRC-hash of each file sector until the archive is closed.
         */
        CHECK_SECTOR_CRC(0x00080000);
        
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
    
    public void setBaseProvider(BaseProvider baseProvider) {
        this.baseProvider = baseProvider;
    }
    
    public void setStreamProvider(StreamProvider streamProvider) {
        this.streamProvider = streamProvider;
    }
    
    public void setOpenFlags(EnumSet<StreamFlag> streamFlags) {
        this.streamFlags = streamFlags;
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
