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

#include "StdAfx.h"
#include <jni.h>
#include "DlogFp.h"
#include "DlogEC.h"
#include <openssl/ec.h>
#include <iostream>

using namespace std;

/* 
 * function createCurve		: Creates the Fp curve.
 * param pBytes				: Bytes of the group's modulus.
 * param aBytes				: The parameter a of the curve equation, y^2 + x*y = x^3 + a*x^2 + b.
 * param bBytes				: The parameter b of the curve equation, y^2 + x*y = x^3 + a*x^2 + b.
 * return					: Pointer to the created curve.
 */
JNIEXPORT jlong JNICALL Java_edu_biu_scapi_primitives_dlog_openSSL_OpenSSLDlogECFp_createCurve
  (JNIEnv *env, jobject, jbyteArray pBytes, jbyteArray aBytes, jbyteArray bBytes){

	  BN_CTX *ctx;
	  EC_GROUP *curve;
	  BIGNUM *a, *b, *p;
	 
	  //Convert the jbyteArrays to c++ notation.
	  jbyte* p_bytes  = (jbyte*) env->GetByteArrayElements(pBytes, 0);
	  jbyte* a_bytes  = (jbyte*) env->GetByteArrayElements(aBytes, 0);
	  jbyte* b_bytes  = (jbyte*) env->GetByteArrayElements(bBytes, 0);
	

	  // Set up the BN_CTX.
	  if(NULL == (ctx = BN_CTX_new())) return 0;

	  // Set the values of the curve parameters.
	  if(NULL == (a = BN_bin2bn((unsigned char*) a_bytes, env->GetArrayLength(aBytes), NULL))) return 0;
	  if(NULL == (b = BN_bin2bn((unsigned char*)b_bytes, env->GetArrayLength(bBytes), NULL))) return 0;
	  if(NULL == (p = BN_bin2bn((unsigned char*)p_bytes, env->GetArrayLength(pBytes), NULL))) return 0;
	
	  // Create the curve.
	  if(NULL == (curve = EC_GROUP_new_curve_GFp(p, a, b, ctx))) return 0;

	  //Release the allocated memory.
	  BN_free(p);
	  BN_free(b);
	  BN_free(a);
	  env ->ReleaseByteArrayElements(pBytes, (jbyte*) p_bytes, 0);
	  env ->ReleaseByteArrayElements(aBytes, (jbyte*) a_bytes, 0);
	  env ->ReleaseByteArrayElements(bBytes, (jbyte*) b_bytes, 0);
	  
	  //Create Dlog group with the curve and ctx.
	  DlogEC* dlog = new DlogEC(curve, ctx);
	  return (long) dlog;
}

/* 
 * function initCurve		: Initialize the Fp curve with generator and order.
 * param dlog				: Pointer to the native Dlog object.
 * param generator			: Pointer to the generator point.
 * param qBytes				: Bytes of the group's order.
 * return					: 1 if the initialization succedded; False, otherwise.
 */
JNIEXPORT int JNICALL Java_edu_biu_scapi_primitives_dlog_openSSL_OpenSSLDlogECFp_initCurve
  (JNIEnv *env, jobject, jlong dlog, jlong generator, jbyteArray qBytes){
	  
	  //Convert the order into BIGNUM object.
	  BIGNUM *order;
	  jbyte* q_bytes  = (jbyte*) env->GetByteArrayElements(qBytes, 0);

	  if(NULL == (order = BN_bin2bn((unsigned char*)q_bytes, env->GetArrayLength(qBytes), NULL))) return 0;

	  // Set the generator and the order.
	  if(1 != EC_GROUP_set_generator(((DlogEC*) dlog)->getCurve(), (EC_POINT*) generator, order, NULL))
		  return 0;
	
	  //Release the allocated memory.
	  BN_free(order);
	  env ->ReleaseByteArrayElements(qBytes, (jbyte*) q_bytes, 0);

	  return 1;
}
