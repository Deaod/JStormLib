package de.deaod.jstormlib.exceptions;

public class MPQAlreadyDeletedException extends MPQException {
    
    /**
     * 
     */
    private static final long serialVersionUID = -6188913048282299863L;
    
    public MPQAlreadyDeletedException() {
        super();
    }
    
    public MPQAlreadyDeletedException(String msg) {
        super(msg);
    }
}
