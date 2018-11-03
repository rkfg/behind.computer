/*
 * AddCitizen.cpp
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#include "AddCitizen.h"
#include <Wt/WLineEdit.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WMessageBox.h>
#include "domain/Citizen.h"

using namespace std;
using namespace Wt;

AddCitizen::AddCitizen(dbo::Session& session, WContainerWidget* parent) :
		WTemplate(tr("add-form")), m_session(session) {
	addFunction("tr", Functions::tr);
	tb_username = bindWidget("username_edit", make_unique<WLineEdit>());
	tb_fullname = bindWidget("fullname_edit", make_unique<WLineEdit>());
	b_add = bindWidget("button_add", make_unique<WPushButton>(tr("add")));
	b_add->clicked().connect(this, &AddCitizen::onAddClick);
}

void AddCitizen::onAddClick() {
	auto fullname = tb_fullname->text();
	auto username = tb_username->text();
	if (fullname.empty() || username.empty()) {
		WMessageBox::show(tr("error"), tr("empty-fields"), StandardButton::Ok);
		return;
	}
	if (WMessageBox::show(tr("add?"),
			tr("add-citizen?").arg(fullname).arg(username),
			StandardButton::Ok | StandardButton::Cancel)
			== StandardButton::Cancel) {
		return;
	}
	auto citizen = make_unique<Citizen>();
	citizen->fullname = fullname;
	citizen->username = username;
	dbo::Transaction t(m_session);
	m_session.add(move(citizen));
	WMessageBox::show(tr("added"),
			tr("new-citizen-added").arg(fullname).arg(username),
			StandardButton::Ok);
	m_citizenAdded.emit();
}
