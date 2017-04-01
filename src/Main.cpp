#include <iostream>
#include <stdexcept>

#include <omniORB4/CORBA.h>
//#include <orbsvcs/CosNamingC.h>

#include "ForumImpl.h"

using namespace std;
using namespace Test;
using namespace PortableServer;

int main(int argc, char** argv) {
	// Declare ORB and servant object
	CORBA::ORB_var orb;
	

	try {
		// Initialize the ORB.
		orb = CORBA::ORB_init(argc, argv);
		// Get a reference to the root POA
		CORBA::Object_var rootPOAObj = orb->resolve_initial_references("RootPOA");
		// Narrow it to the correct type
		POA_var rootPOA = POA::_narrow(rootPOAObj.in());

		// Create POA policies
		CORBA::PolicyList policies;
		policies.length(1);

		policies[0] = rootPOA->create_thread_policy(PortableServer::SINGLE_THREAD_MODEL);

		// Get the POA manager object
		POAManager_var manager = rootPOA->the_POAManager();

		// Create a new POA with specified policies
		POA_var myPOA = rootPOA->create_POA("myPOA", manager, policies);

		// Free policies
		CORBA::ULong len = policies.length();
		for (CORBA::ULong i = 0; i < len; i++) {
			policies[i]->destroy();
		}

		// Get a reference to the Naming Service root_context
		CORBA::Object_var rootContextObj = orb->resolve_initial_references("NameService");

		// Narrow to the correct type
		CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(rootContextObj.in());

		// Create a reference to the servant
		ForumImpl forum(orb);
		
		// Activate object
		ObjectId_var myObjID = myPOA->activate_object(forum);

		// Get a CORBA reference with the POA through the servant
		CORBA::Object_var o = myPOA->servant_to_reference(forum);

		// The reference is converted to a character string
		CORBA::String_var s = orb->object_to_string(o);
		cout << "The IOR of the object is: " << s.in() << endl;

		CosNaming::Name name;
		name.length(1);
		name[0].id = (const char *) "CryptographicService";
		name[0].kind = (const char *) "";

		// Bind the object into the name service
		nc->rebind(name,o);

		// Activate the POA
		manager->activate();
		cout << "The server is ready. Awaiting for incoming requests..." << endl;

		// Start the ORB
		orb->run();

	} catch(const CORBA::Exception& e) {
		// Handles CORBA exceptions
		//cerr << e << endl;
	}

	// Decrement reference count
	/*if (CrypImpl)
	CrypImpl->_remove_ref();*/

	// End CORBA
	if (!CORBA::is_nil(orb)){
		try{
			orb->destroy();
			cout << "Ending CORBA..." << endl;
		} catch (const CORBA::Exception& e) {
			// cout << "orb->destroy() failed:" << e << endl;
			return 1;
		}
	}

	return 0;
}
