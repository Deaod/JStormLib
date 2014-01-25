package de.deaod.jstormlib.exceptions;

public class MPQAlreadyExistsException extends MPQException {
    
    /**
     * 
     */
    private static final long serialVersionUID = -1134762597754552816L;
    
    public MPQAlreadyExistsException() {
        super();
    }
    
    public MPQAlreadyExistsException(String msg) {
        super(msg);
    }
}
