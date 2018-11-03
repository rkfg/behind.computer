/*
 * AddCitizen.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef ADDCITIZEN_H_
#define ADDCITIZEN_H_

#include <Wt/WSignal.h>
#include <Wt/WTemplate.h>

namespace dbo = Wt::Dbo;

class AddCitizen: public Wt::WTemplate {
private:
	Wt::WLineEdit* tb_username;
	Wt::WLineEdit* tb_fullname;
	Wt::WPushButton* b_add;
	dbo::Session& m_session;
	Wt::Signal<> m_citizenAdded;
public:
	AddCitizen(dbo::Session& session, Wt::WContainerWidget* parent = 0);
	void onAddClick();
	Wt::Signal<>& citizenAdded() {
		return m_citizenAdded;
	}
};

#endif /* ADDCITIZEN_H_ */
