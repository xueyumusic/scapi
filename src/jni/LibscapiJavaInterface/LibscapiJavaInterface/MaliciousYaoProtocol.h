/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <string>
#include <stdio.h>
#include <libscapi\include\infra\ConfigFile.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\primitives\CommunicationConfig.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\primitives\ExecutionParameters.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\OfflineOnline\primitives\BucketLimitedBundle.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\OfflineOnline\primitives\BucketBundle.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\OfflineOnline\specs\OfflineProtocolP1.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\OfflineOnline\specs\OfflineProtocolP2.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\OfflineOnline\specs\OnlineProtocolP1.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\OfflineOnline\specs\OnlineProtocolP2.hpp>
#include <libscapi\protocols\MaliciousYao\lib\include\primitives\CheatingRecoveryCircuitCreator.hpp>

/* Header for class edu_biu_scapi_protocols_maliciousYao_MaliciousYaoParty */

#ifndef _Included_edu_biu_scapi_protocols_maliciousYao
#define _Included_edu_biu_scapi_protocols_maliciousYao
#ifdef __cplusplus
extern "C" {
#endif
	/*
	* Class:     edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOfflineParty
	* Method:    createYaoParty
	* Signature: (ILjava/lang/String;)J
	*/
	JNIEXPORT jlong JNICALL Java_edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOfflineParty_createYaoParty
		(JNIEnv *, jobject, jint, jstring);

	/*
	* Class:     edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOfflineParty
	* Method:    runProtocol
	* Signature: (IJ)V
	*/
	JNIEXPORT void JNICALL Java_edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOfflineParty_runProtocol
		(JNIEnv *, jobject, jint, jlong);

	/*
	* Class:     edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOfflineParty
	* Method:    deleteMaliciousYao
	* Signature: (IJ)V
	*/
	JNIEXPORT void JNICALL Java_edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOfflineParty_deleteMaliciousYao
		(JNIEnv *, jobject, jint, jlong);

	/*
	* Class:     edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOnlineParty
	* Method:    createYaoParty
	* Signature: (ILjava/lang/String;)J
	*/
	JNIEXPORT jlong JNICALL Java_edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOnlineParty_createYaoParty
		(JNIEnv *, jobject, jint, jstring);

	/*
	* Class:     edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOnlineParty
	* Method:    runProtocol
	* Signature: (IJII)[B
	*/
	JNIEXPORT jbyteArray JNICALL Java_edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOnlineParty_runProtocol
		(JNIEnv *, jobject, jint, jlong, jint, jint);

	/*
	* Class:     edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOnlineParty
	* Method:    deleteMaliciousYao
	* Signature: (IJ)V
	*/
	JNIEXPORT void JNICALL Java_edu_biu_SCProtocols_NativeMaliciousYao_MaliciousYaoOnlineParty_deleteMaliciousYao
		(JNIEnv *, jobject, jint, jlong);

#ifdef __cplusplus
}

using namespace std;

/**
 * This struct contains some parameters used by the malicious yao parties
 */
struct MaliciousYaoConfig {

	string main_circuit_file;	//Name of the main circuit file
	string cr_circuit_file;		//Name of the cheating recovery circuit file

	//Parameters that determines the number of buckets, buckets sizes, probability and security.
	int n1, b1, s1;
	int n2, b2, s2;
	double p1, p2;
	int num_threads;	//Number of treads to use in the execution

	//The following parameters used by the online protocol:
	string main_matrix;			//Name of the main matrix file
	string cr_matrix;			// Name of the cheating recovery matrix file
	string input_file_1;		//Name of p1 inputs file
	string input_file_2;		//Name of p2 inputs file
	string bucket_prefix_main1, bucket_prefix_main2; //Prefix for p1 buckets
	string bucket_prefix_cr1, bucket_prefix_cr2;	 //Prefix for p2 buckets
	string parties_file;		//Name of the file that manage the communication
	string ec_file;				//Name of the file contains the elliptic curves.
	
	/**
	 * Read the config file and set all parameters.
	 */
	MaliciousYaoConfig(string config_file) {
#ifdef _WIN32
		string os = "Windows";
#else
		string os = "Linux";
#endif
		//cout << "in config constructor" << endl;
		ConfigFile cf(config_file);
		//cout << "after create ConfigFile" << endl;
		string input_section = cf.Value("", "input_section") + "-" + os;
		main_circuit_file = cf.Value(input_section, "main_circuit_file");
		cr_circuit_file = cf.Value(input_section, "cr_circuit_file");
		main_matrix = cf.Value(input_section, "main_matrix");
		cr_matrix = cf.Value(input_section, "cr_matrix");
		input_file_1 = cf.Value(input_section, "input_file_party_1");
		input_file_2 = cf.Value(input_section, "input_file_party_2");
		bucket_prefix_main1 = cf.Value(input_section, "bucket_prefix_main1");
		bucket_prefix_cr1 = cf.Value(input_section, "bucket_prefix_cr1");
		bucket_prefix_main2 = cf.Value(input_section, "bucket_prefix_main2");
		bucket_prefix_cr2 = cf.Value(input_section, "bucket_prefix_cr2");
		parties_file = cf.Value(input_section, "parties_file");
		ec_file = cf.Value(input_section, "ec_file");
		n1 = stoi(cf.Value("", "n1"));
		b1 = stoi(cf.Value("", "b1"));
		s1 = stoi(cf.Value("", "s1"));
		p1 = stof(cf.Value("", "p1"));
		n2 = stoi(cf.Value("", "n2"));
		b2 = stoi(cf.Value("", "b2"));
		s2 = stoi(cf.Value("", "s2"));
		p2 = stof(cf.Value("", "p2"));
		num_threads = stoi(cf.Value("", "num_threads"));
	}

	MaliciousYaoConfig() {}
};


/**
 * This class holds some values used in the protocol.
 * A pointer to this class is sent to the java object as the pointer to the native implementation.
 */
class MaliciousYaoHandler {
private:
	long party;										//The actual party of the protocol. Can be either p1 or p2, online or offline.
	MaliciousYaoConfig yaoConfig;					//Holds the protocol cofiguration 
	shared_ptr<CommunicationConfig> commConfig;		//manage the communication
	boost::asio::io_service* io_service;			//used in the communication
	vector<shared_ptr<BucketBundle>> mainBucketsP1; //used in online p1
	vector<shared_ptr<BucketBundle>> crBucketsP1;	//used in online p1
	vector<shared_ptr<BucketLimitedBundle>> mainBucketsP2; //used in online p2
	vector<shared_ptr<BucketLimitedBundle>> crBucketsP2;   //used in online p2
	shared_ptr<ExecutionParameters> mainExecution;	//Used in Online p2
	shared_ptr<ExecutionParameters> crExecution;	//Used in Online p2
	shared_ptr<KProbeResistantMatrix> mainMatrix, crMatrix; //Used in Online p2
	shared_ptr<CircuitInput> input;					//Input of the protocol

public:
	/**
	 * This constructor used by the offline protocol (p1 and p2)
	 */
	MaliciousYaoHandler(long party, MaliciousYaoConfig yaoConfig, const shared_ptr<CommunicationConfig> & commConfig, boost::asio::io_service* io_service)
		: party(party), yaoConfig(yaoConfig), commConfig(commConfig), io_service(io_service) {}

	/**
	* This constructor used by party one of the online protocol
	*/
	MaliciousYaoHandler(MaliciousYaoConfig yaoConfig, const shared_ptr<CommunicationConfig> & commConfig, boost::asio::io_service* io_service, 
		const vector<shared_ptr<BucketBundle>> & mainBuckets, const vector<shared_ptr<BucketBundle>> & crBuckets, const shared_ptr<CircuitInput> & input)
		: yaoConfig(yaoConfig), commConfig(commConfig), io_service(io_service), mainBucketsP1(mainBuckets), crBucketsP1(crBuckets), input(input){}

	/**
	* This constructor used by party two of the online protocol
	*/
	MaliciousYaoHandler(MaliciousYaoConfig yaoConfig, const shared_ptr<CommunicationConfig> & commConfig, boost::asio::io_service* io_service, 
		const shared_ptr<ExecutionParameters> & mainExecution, const shared_ptr<ExecutionParameters> & crExecution, const shared_ptr<KProbeResistantMatrix> & mainMatrix, 
		const shared_ptr<KProbeResistantMatrix> & crMatrix, const vector<shared_ptr<BucketLimitedBundle>> & mainBuckets, const vector<shared_ptr<BucketLimitedBundle>> & crBuckets,
		const shared_ptr<CircuitInput> & input)
		: yaoConfig(yaoConfig), commConfig(commConfig), io_service(io_service), mainExecution(mainExecution), crExecution(crExecution),
		  mainMatrix(mainMatrix), crMatrix(crMatrix), mainBucketsP2(mainBuckets), crBucketsP2(crBuckets), input(input){}

	/**
	 * The party should be deleted outside since this class does not know which concrete party it have.
	 * This destructor close the channel and edeltes it. All other members are shared pointers so there is no need to delete them.
	 */
	~MaliciousYaoHandler() {
		io_service->stop();
		delete io_service;
	}

	long getParty() { return party; }
	MaliciousYaoConfig getConfig() { return yaoConfig; }
	shared_ptr<CommunicationConfig> getCommConfig() { return commConfig; }

	shared_ptr<ExecutionParameters> getMainExecution() { return mainExecution; }
	shared_ptr<ExecutionParameters> getCRExecution() { return crExecution; }
	shared_ptr<KProbeResistantMatrix> getMainMatrix() { return mainMatrix; }
	shared_ptr<KProbeResistantMatrix> getCRMatrix() { return crMatrix; }
	vector<shared_ptr<BucketBundle>> getMainBuckets1() {	return mainBucketsP1; }
	vector<shared_ptr<BucketBundle>> getCRBuckets1() { return crBucketsP1; }
	vector<shared_ptr<BucketLimitedBundle>> getMainBuckets2() { return mainBucketsP2; }
	vector<shared_ptr<BucketLimitedBundle>> getCRBuckets2() { return crBucketsP2; }
	shared_ptr<CircuitInput> getInput() { return input; }
};

//Used in party two of the online protocol.
block** saveBucketGarbledTables(int size, BucketLimitedBundle * bucket);
void restoreBucketTables(int size, BucketLimitedBundle* bucket, block** tables);


#endif
#endif
