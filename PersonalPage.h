/*
 * PersonalPage.h
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#ifndef PERSONALPAGE_H_
#define PERSONALPAGE_H_

#include <Wt/WTemplate>

using namespace Wt;
namespace dbo = Wt::Dbo;

class PersonalPage: public WTemplate {
private:
	dbo::Session& m_session;
	WString m_hostName;
public:
	void reload();
	PersonalPage(dbo::Session& session, const WString& hostName,
			WContainerWidget* parent = 0);
};

#endif /* PERSONALPAGE_H_ */
