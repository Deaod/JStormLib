package de.deaod.jstormlib;

public enum MPQVerifyArchiveResult {
    NO_SIGNATURE(0),
    VERIFY_FAILED(1),
    WEAK_SIGNATURE_OK(2),
    WEAK_SIGNATURE_ERROR(3),
    STRONG_SIGNATURE_OK(4),
    STRONG_SIGNATURE_ERROR(5);
    
    private int value;
    
    private MPQVerifyArchiveResult(int value) {
        this.value = value;
    }
    
    static MPQVerifyArchiveResult fromInteger(int value) {
        for (MPQVerifyArchiveResult result : MPQVerifyArchiveResult.values()) {
            if (result.value == value)
                return result;
        }
        return null;
    }
}
