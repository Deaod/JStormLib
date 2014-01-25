package de.deaod.jstormlib;

public enum MPQVerifyArchiveResult {
    /**
     * There is no known signature present in the MPQ.
     */
    NO_SIGNATURE(0),
    
    /**
     * An error occured during verifying the signature, such as no memory or read error.
     */
    VERIFY_FAILED(1),
    
    /**
     * Weak digital signature was found in the archive and has been successfully verified. The signature is valid.
     */
    WEAK_SIGNATURE_OK(2),
    
    /**
     * Weak digital signature was found in the archive but its verification failed. The signature is not valid.
     */
    WEAK_SIGNATURE_ERROR(3),
    
    /**
     * Strong digital signature was found in the archive and has been successfully verified. The signature is valid.
     */
    STRONG_SIGNATURE_OK(4),
    
    /**
     * Strong digital signature was found in the archive but its verification failed. Either the signature is not valid
     * or StormLib doesn't have the proper public key.
     */
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
