/*
 * AddCitizen.cpp
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#include "AddCitizen.h"
#include <Wt/WLineEdit>
#include <Wt/WVBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WMessageBox>
#include "domain/Citizen.h"

AddCitizen::AddCitizen(dbo::Session& session, WContainerWidget* parent) :
		WTemplate(tr("add-form"), parent), m_session(session) {
	addFunction("tr", Functions::tr);
	tb_username = new WLineEdit();
	tb_fullname = new WLineEdit();
	b_add = new WPushButton(tr("add"));
	bindWidget("username_edit", tb_username);
	bindWidget("fullname_edit", tb_fullname);
	bindWidget("button_add", b_add);
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
	auto citizen = new Citizen();
	citizen->fullname = fullname;
	citizen->username = username;
	dbo::Transaction t(m_session);
	m_session.add(citizen);
	WMessageBox::show(tr("added"),
			tr("new-citizen-added").arg(fullname).arg(username),
			StandardButton::Ok);
	m_citizenAdded.emit();
}
