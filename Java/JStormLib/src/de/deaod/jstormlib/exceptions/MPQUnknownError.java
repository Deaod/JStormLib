package de.deaod.jstormlib.exceptions;

public class MPQUnknownError extends MPQRuntimeException {
    
    /**
     * 
     */
    private static final long serialVersionUID = -1257381238554264838L;
    
    public MPQUnknownError() {
        super();
    }
    
    public MPQUnknownError(String msg) {
        super(msg);
    }
}
