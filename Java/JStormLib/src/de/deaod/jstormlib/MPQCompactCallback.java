package de.deaod.jstormlib;

public interface MPQCompactCallback {
    public void compactCallback(MPQCompressionWorkType workType, long bytesProcessed, long bytesTotal);
}
