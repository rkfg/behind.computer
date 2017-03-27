/*
 * MainPage.cpp
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#include "MainPage.h"

#include <Wt/Dbo/collection_impl.h>
#include <Wt/Dbo/Query_impl.h>
#include <Wt/Dbo/collection>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/Query>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/Transaction>
#include <Wt/WString>

#include "domain/Citizen.h"
#include "TweetsContainer.h"
#include "utils.h"

using namespace std;

void MainPage::reload() {
	bindWidget("tweets", new TweetsContainer(m_session));
}

MainPage::MainPage(dbo::Session& session, WContainerWidget* parent) :
		WTemplate(tr("main-template"), parent), m_session(session) {
	dbo::Transaction t(m_session);
	auto citizensWidget = new WContainerWidget();
	for (auto& citizen : m_session.find<Citizen>().orderBy("username asc").resultList()) {
		auto citizenRow = new WTemplate(tr("citizen-row"), citizensWidget);
		citizenRow->bindString("fullname", citizen->fullname);
		citizenRow->bindString("pageurl", PAGEURL(citizen->username));
	}
	bindWidget("citizens", citizensWidget);
	auto citizens = m_session.find<Citizen>().resultList();
	bindInt("citizens_count", citizens.size());
	reload();
}
