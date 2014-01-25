package de.deaod.jstormlib.exceptions;

public class MPQInsufficientBufferException extends MPQException {
    
    /**
     * 
     */
    private static final long serialVersionUID = 5367443863888173249L;
    
    public MPQInsufficientBufferException() {
        super();
    }
    
    public MPQInsufficientBufferException(String msg) {
        super(msg);
    }
}
