package de.deaod.jstormlib.exceptions;

public class MPQUnexpectedEOFException extends MPQException {
    
    /**
     * 
     */
    private static final long serialVersionUID = -3632994367525224861L;
    
    public MPQUnexpectedEOFException() {
        super();
    }
    
    public MPQUnexpectedEOFException(String msg) {
        super(msg);
    }
}
