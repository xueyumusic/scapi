#include "stdafx.h"
#include "RSAPss.h"
#include "cryptlib.h"
#include "Utils.h"
#include <osrng.h>
#include <rsa.h>
#include <iostream>

using namespace std;
using namespace CryptoPP;

/*
 * function createRSASigner : Creates the object that operates the sign 
 * return jlong				: pointer to the native signer
 */
JNIEXPORT jlong JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_createRSASigner
  (JNIEnv *, jobject){
	  //creates the signature object
	  RSASSA_PKCS1v15_SHA_Signer* signer = new RSASSA_PKCS1v15_SHA_Signer();

	  //return the signer
	  return (jlong) signer;
}

/*
 * function createRSAVerifier : Creates the object that operates the verification 
 * return jlong				  : pointer to the native verifier
 */
JNIEXPORT jlong JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_createRSAVerifier
  (JNIEnv *, jobject){
	  //creates the verification object
	  RSASSA_PKCS1v15_SHA_Verifier* verifier = new RSASSA_PKCS1v15_SHA_Verifier();

	  //return the verifier
	  return (jlong) verifier;
}

/*
 * function initRSAVerifier   : Initializes the object that operates the verification with RSA parameters
 * param verifier			  : The pointer to the verification object 
 * param modulus			  : RSA modulus
 * param pubExp				  : public exponent
 * return jlong				  : pointer to the native verifier
 */
JNIEXPORT void JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_initRSAVerifier
  (JNIEnv * env, jobject, jlong verifier, jbyteArray modulus, jbyteArray pubExp){
	   Integer n, e;
	  Utils utils;

	  // get the Integers values for the RSA permutation 
	  n = utils.jbyteArrayToCryptoPPInteger(env, modulus);
	  e = utils.jbyteArrayToCryptoPPInteger(env, pubExp);
	  
	  //create pointer to RSAFunction object
	  RSAFunction* rsaFunc = new RSAFunction(); //assign RSAFunction to the pointer

	  //initialize the RSAFunction object with the RSA values
	  rsaFunc->Initialize(n, e);

	  //create a PublicKey from the function
	  RSA::PublicKey publicKey(*rsaFunc);

	  //set the public key to the verifier 
	  ((RSASSA_PKCS1v15_SHA_Verifier * ) verifier)->AccessPublicKey().AssignFrom(publicKey);
}

/*
 * function initRSACrtSigner  : Initializes the object that operates the signing with RSA CRT parameters
 * param signer				  : The pointer to the signing object 
 * param modulus			  : RSA modulus
 * param pubExp				  : public exponent
 * param privExp			  : private exponent
 * param prime1				  : prime number, such that Prime1*prime2 = modulus
 * param prime2				  : prime number, such that Prime1*prime2 = modulus
 * param primeExponent1		   
 * param primeExponent2		  
 * param crt				  : crt coefficient
 * return jlong				  : pointer to the native signer
 */
JNIEXPORT void JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_initRSACrtSigner
  (JNIEnv * env, jobject, jlong signer, jbyteArray modulus, jbyteArray pubExp, jbyteArray privExp, jbyteArray prime1, 
  jbyteArray prime2, jbyteArray primeExponent1, jbyteArray primeExponent2, jbyteArray crt){
	  Integer n, e, d, p, q, dp, dq, u;
	  Utils utils;

	  // get the Integers values for the RSA permutation 
	  n = utils.jbyteArrayToCryptoPPInteger(env, modulus);
	  e = utils.jbyteArrayToCryptoPPInteger(env, pubExp);
	  d = utils.jbyteArrayToCryptoPPInteger(env, privExp);
	  p = utils.jbyteArrayToCryptoPPInteger(env, prime1);
	  q = utils.jbyteArrayToCryptoPPInteger(env, prime2);
	  dp = utils.jbyteArrayToCryptoPPInteger(env, primeExponent1);
	  dq = utils.jbyteArrayToCryptoPPInteger(env, primeExponent2);
	  u = utils.jbyteArrayToCryptoPPInteger(env, crt);

	  //create pointer to InvertibleRSAFunction object
	  InvertibleRSAFunction *invRsaFunc = new InvertibleRSAFunction;

	  //initialize the invert Rsa Function object with the RSA values
	  invRsaFunc-> Initialize(n, e, d, p, q, dp, dq, u);

	  //create a private key from the function
	  RSA::PrivateKey privateKey(*invRsaFunc);
	  
	  //set the private key to the signer 
	  ((RSASSA_PKCS1v15_SHA_Signer * ) signer)->AccessKey().AssignFrom(privateKey);
}

/*
 * function initRSASigner     : Initializes the object that operates the signing with RSA parameters
 * param signer				  : The pointer to the signing object 
 * param modulus			  : RSA modulus
 * param pubExp				  : public exponent
 * param privExp			  : private exponent
 * return jlong				  : pointer to the native signer
 */
JNIEXPORT void JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_initRSASigner
  (JNIEnv * env, jobject, jlong signer, jbyteArray modulus, jbyteArray pubExp, jbyteArray privExp){
	  Integer n, e, d;
	  Utils utils;

	  // get the Integers values for the RSA permutation 
	  n = utils.jbyteArrayToCryptoPPInteger(env, modulus);
	  e = utils.jbyteArrayToCryptoPPInteger(env, pubExp);
	  d = utils.jbyteArrayToCryptoPPInteger(env, privExp);

	  //create pointer to InvertibleRSAFunction object
	  InvertibleRSAFunction* invRsaFunc = new InvertibleRSAFunction;

	  //initialize the trapdoor object with the RSA values
	  invRsaFunc->Initialize(n, e, d);

	  //create a private key from the function
	  RSA::PrivateKey privateKey(*invRsaFunc);
	  
	  //set the private key to the signer 
	  ((RSASSA_PKCS1v15_SHA_Signer * ) signer)->AccessKey().AssignFrom(privateKey);
}

/*
 * function doSign		: Sign the given message and returns the signature
 * param signer			: The pointer to the signing object 
 * param msg			: message to sign
 * param length			: the message length
 * return jbyteArray	: the generated signature
 */
JNIEXPORT jbyteArray JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_doSign
  (JNIEnv *env, jobject, jlong signer, jbyteArray msg, jint length){

	// cast the signer pointer to the actual signer object
	RSASSA_PKCS1v15_SHA_Signer * signerLocal = (RSASSA_PKCS1v15_SHA_Signer * )signer;
		
	//declare a byte array in c++ where to hold the input msg
	byte *msgBytes = (byte*)env->GetByteArrayElements(msg, 0);
	   
	// Create signature space
	size_t maxSigSize = signerLocal->MaxSignatureLength();
	byte *signature = new byte[maxSigSize];
	
	// Actually perform sign
	AutoSeededRandomPool randPool;
	size_t actualSigSize = signerLocal->SignMessage(randPool, msgBytes, length, signature);
	
	//create a JNI byte array from the signature
	jbyteArray retSignature= env->NewByteArray(actualSigSize);
	env->SetByteArrayRegion(retSignature, 0, actualSigSize, (jbyte*)signature);
	return retSignature;
}

/*
 * function doVerify	: Verify if the given signature is valid to the given message 
 * param verifier		: The pointer to the verification object 
 * param signature		: signature to verify
 * param msg			: message
 * param length			: message length
 * return jboolean		: true if the signature is vcalid. false otherwise.
 */
JNIEXPORT jboolean JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_digitalSignature_CryptoPPRSAPss_doVerify
  (JNIEnv *env, jobject, jlong verifier, jbyteArray signature, jbyteArray msg, jint length){
	//declare a byte arrays in c++ where to hold the input msg and signature
	byte *msgBytes = (byte*)env->GetByteArrayElements(msg, 0);
	byte *sigBytes = (byte*)env->GetByteArrayElements(signature, 0);
	int sigLen = env->GetArrayLength(signature);

	// cast the verifier pointer to the actual verifier object
	RSASSA_PKCS1v15_SHA_Verifier* verifierLocal = (RSASSA_PKCS1v15_SHA_Verifier*) verifier;

	//verifies the signature.
	return verifierLocal->VerifyMessage(msgBytes, length, sigBytes, sigLen);

}