#ifndef __FORUMIMPL_H__
#define __FORUMIMPL_H__


#include <iostream>
#include <string>

#include <omniORB4/CORBA.h>
#include "Test.h"

using namespace Test;

class ForumImpl : virtual public POA_Test::Forum, virtual public PortableServer::RefCountServantBase

{
	CORBA::ORB_var orb; // Reference to CORBA ORB

	public:
		ForumImpl(CORBA::ORB_var orb){this->orb = orb;}
		::CORBA::Boolean postMessage(const ::Test::Message& m);
		Message* getMessage(const char* title);
		::CORBA::Boolean removeMessage(const char* title);
		char* theme();
		char* moderator();
	
	
	virtual ::CORBA::Boolean shutdown() throw(::CORBA::SystemException)
		{
			orb->shutdown(false);
			return true;
		}
		
		
};

#endif
