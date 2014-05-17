package de.deaod.jstormlib.data;

public final class MPQUserDataHeader {
    private final int userDataSize;
    private final int mpqHeaderOffset;
    private final int userDataHeaderSize;
    
    private MPQUserDataHeader(final int userDataSize, final int mpqHeaderOffset, final int userDataHeaderSize) {
        this.userDataSize = userDataSize;
        this.mpqHeaderOffset = mpqHeaderOffset;
        this.userDataHeaderSize = userDataHeaderSize;
    }
    
    public final int getUserDataSize() {
        return this.userDataSize;
    }
    
    public final int getMpqHeaderOffset() {
        return this.mpqHeaderOffset;
    }
    
    public final int getUserDataHeaderSize() {
        return this.userDataHeaderSize;
    }
    
}
