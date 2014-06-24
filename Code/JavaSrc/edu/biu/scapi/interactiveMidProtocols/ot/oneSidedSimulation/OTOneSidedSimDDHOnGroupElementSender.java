/**
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* 
* Copyright (c) 2012 - SCAPI (http://crypto.biu.ac.il/scapi)
* This file is part of the SCAPI project.
* DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* 
* We request that any publication and/or code referring to and/or based on SCAPI contain an appropriate citation to SCAPI, including a reference to
* http://crypto.biu.ac.il/SCAPI.
* 
* SCAPI uses Crypto++, Miracl, NTL and Bouncy Castle. Please see these projects for any further licensing issues.
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* 
*/
package edu.biu.scapi.interactiveMidProtocols.ot.oneSidedSimulation;

import java.io.IOException;
import java.security.SecureRandom;

import edu.biu.scapi.exceptions.CheatAttemptException;
import edu.biu.scapi.exceptions.InvalidDlogGroupException;
import edu.biu.scapi.exceptions.SecurityLevelException;
import edu.biu.scapi.interactiveMidProtocols.ot.OTSInput;
import edu.biu.scapi.interactiveMidProtocols.ot.OTSMsg;
import edu.biu.scapi.interactiveMidProtocols.ot.OTOnGroupElementSInput;
import edu.biu.scapi.interactiveMidProtocols.ot.OTOnGroupElementSMsg;
import edu.biu.scapi.primitives.dlog.DlogGroup;
import edu.biu.scapi.primitives.dlog.GroupElement;
import edu.biu.scapi.securityLevel.OneSidedSimulation;

/**
 * Concrete implementation of the sender side in oblivious transfer based on the DDH assumption that achieves 
 * privacy for the case that the sender is corrupted and simulation in the case that the receiver 
 * is corrupted.<p>
 * 
 * For more information see Protocol 7.3 page 185 of <i>Efficient Secure Two-Party Protocols</i> by Hazay-Lindell.<p>
 * 
 * This class derived from OTOneSidedSimDDHSenderAbs and implements the functionality 
 * related to the GroupElement inputs.<p>
 * 
 * @author Cryptography and Computer Security Research Group Department of Computer Science Bar-Ilan University (Moriya Farbstein)
 *
 */
public class OTOneSidedSimDDHOnGroupElementSender extends OTOneSidedSimDDHSenderAbs implements OneSidedSimulation{
		
	/**
	 * Constructor that chooses default values of DlogGroup and SecureRandom.
	 * @throws CheatAttemptException 
	 */
	public OTOneSidedSimDDHOnGroupElementSender() throws IOException, ClassNotFoundException, CheatAttemptException{
		super();
	}
	
	/**
	 * Constructor that sets the given channel, dlogGroup and random.
	 * @param dlog must be DDH secure.
	 * @param random
	 * @throws SecurityLevelException if the given DlogGroup is not DDH secure.
	 * @throws InvalidDlogGroupException if the given dlog is invalid.
	 * @throws CheatAttemptException 
	 */
	public OTOneSidedSimDDHOnGroupElementSender(DlogGroup dlog, SecureRandom random) throws SecurityLevelException, InvalidDlogGroupException, IOException, ClassNotFoundException, CheatAttemptException{
		super(dlog, random);
	}
	
	/**
	 * Runs the following lines from the protocol:
	 * "COMPUTE:
	 *		�	c0 = x0 * k0
	 *		�	c1 = x1 * k1"
	 * @param input MUST be OTSOnGroupElementInput.
	 * @param w0
	 * @param w1
	 * @param k0
	 * @param k1
	 * @return tuple contains (u, v0, v1) to send to the receiver.
	 */
	protected OTSMsg computeTuple(OTSInput input, GroupElement w0, GroupElement w1, GroupElement k0, GroupElement k1) {
		//If input is not instance of OTSOnGroupElementInput, throw Exception.
		if (!(input instanceof OTOnGroupElementSInput)){
			throw new IllegalArgumentException("x0 and x1 should be DlogGroup elements.");
		}
		OTOnGroupElementSInput inputElements = (OTOnGroupElementSInput)input;
		
		//Set x0, x1.
		GroupElement x0 = inputElements.getX0();
		GroupElement x1 = inputElements.getX1();
		
		//Calculate c0:
		GroupElement c0 = dlog.multiplyGroupElements(x0, k0);
		
		//Calculate c1:
		GroupElement c1 = dlog.multiplyGroupElements(x1, k1);
		
		//Create and return sender message.
		return new OTOnGroupElementSMsg(w0.generateSendableData(), 
				c0.generateSendableData(), w1.generateSendableData(), c1.generateSendableData());
	}
}
