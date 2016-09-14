/*
 * AddCitizen.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef ADDCITIZEN_H_
#define ADDCITIZEN_H_

#include <Wt/WSignal>
#include <Wt/WTemplate>

using namespace Wt;
namespace dbo = Wt::Dbo;

class AddCitizen: public WTemplate {
private:
	WLineEdit* tb_username;
	WLineEdit* tb_fullname;
	WPushButton* b_add;
	dbo::Session& m_session;
	Signal<> m_citizenAdded;
public:
	AddCitizen(dbo::Session& session, WContainerWidget* parent = 0);
	void onAddClick();
	Signal<>& citizenAdded() {
		return m_citizenAdded;
	}
};

#endif /* ADDCITIZEN_H_ */
