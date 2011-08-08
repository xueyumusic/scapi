package edu.biu.scapi.primitives.dlog.miracl;

import java.math.BigInteger;
import java.util.logging.Level;

import edu.biu.scapi.generals.Logging;
import edu.biu.scapi.primitives.dlog.DlogGroup;
import edu.biu.scapi.primitives.dlog.ECElement;
import edu.biu.scapi.primitives.dlog.groupParams.ECFpGroupParams;

/**
 * This class is an adapter for Fp points of miracl
 * @author Moriya
 *
 */
public class ECFpPointMiracl implements ECElement{

	private native long createFpPoint(long mip, byte[] x, byte[] y, boolean[] validity);
	private native long createRandomFpPoint(long mip, byte[] p, boolean[] validity);
	private native void deletePointFp(long p);
	
	private long point = 0;
	
	/**
	 * Constructor that accepts x,y values of a point. 
	 * if the values are valid - set the point.
	 * @param x
	 * @param y
	 * @param curve - DlogGroup
	 */
	public ECFpPointMiracl(BigInteger x, BigInteger y, DlogGroup curve){
		//the DlogGroup that matches this class is MiraclAdapterDlogEC
		if (curve instanceof MiraclAdapterDlogEC){
			//creates point - if the values are valid point - return true. else - return false.
			if (!createPoint(x,y,((MiraclAdapterDlogEC) curve).getMip())){
				point = 0;
				throw new IllegalArgumentException("x, y values are not a point on this curve");
			}
			
			//if the DlogGroup is not MiraclAdapterDlogEC throw exception
		} else throw new IllegalArgumentException("DlogGroup type doesn't match the GroupElement type");
	}
	
	/**
	 * Creates a point with the given values.
	 * @param x
	 * @param y
	 * @param mip - MIRACL pointer
	 * @return true if the point is valid. false, otherwise
	 */
	boolean createPoint(BigInteger x, BigInteger y, long mip) {
		
		boolean validity[] = new boolean[1];
		/*
		 * create the point with the given parameters,
		 * and set the point.
		 */
		point = createFpPoint(mip, x.toByteArray(), y.toByteArray(), validity);

		return validity[0];
	}
	
	/**
	 *  Constructor that gets DlogGroup and choose random point in the group
	 * @param curve
	 */
	public ECFpPointMiracl(DlogGroup curve){
		//the DlogGroup that matches this class is MiraclAdapterDlogEC
		if (curve instanceof MiraclAdapterDlogEC){
			boolean validity[] = new boolean[1];
			
			//call for native function that creates random point in the field.
			point = createRandomFpPoint(((MiraclAdapterDlogEC) curve).getMip(), 
								((ECFpGroupParams)curve.getGroupParams()).getP().toByteArray(), validity);
			//if the algorithm for random element failed - throws exception
			if(validity[0]==false){
				point = 0;
				Logging.getLogger().log(Level.WARNING, "couldn't find random element");
			}
				
		} else throw new IllegalArgumentException("DlogGroup type doesn't match the GroupElement type");
		
	}
	
	/**
	 * Constructor that gets pointer to element and set it.
	 * Only our inner functions uses this constructor to set an element. 
	 * The ptr is a result of our DlogGroup functions, such as multiply.
	 * @param ptr - pointer to native point
	 */
	ECFpPointMiracl(long ptr){
		this.point = ptr;
	}
	
	/**
	 * 
	 * @return the pointer to the point
	 */
	public long getPoint(){
		return point;
	}
	
	/**
	 * delete the related point
	 */
	protected void finalize() throws Throwable{
		
		//delete from the dll the dynamic allocation of the point.
		deletePointFp(point);
	}
	
	static {
        System.loadLibrary("MiraclJavaInterface");
 }
}
