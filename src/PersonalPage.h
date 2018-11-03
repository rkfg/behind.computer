/*
 * PersonalPage.h
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#ifndef PERSONALPAGE_H_
#define PERSONALPAGE_H_

#include <Wt/WTemplate.h>

namespace dbo = Wt::Dbo;

class PersonalPage: public Wt::WTemplate {
private:
	dbo::Session& m_session;
	Wt::WString m_hostName;
public:
	void reload();
	PersonalPage(dbo::Session& session, const Wt::WString& hostName);
};

#endif /* PERSONALPAGE_H_ */
