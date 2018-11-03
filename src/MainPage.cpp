/*
 * MainPage.cpp
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#include "MainPage.h"

#include <Wt/Dbo/collection_impl.h>
#include <Wt/Dbo/Query_impl.h>
#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/Query.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/Transaction.h>
#include <Wt/WString.h>

#include "domain/Citizen.h"
#include "TweetsContainer.h"
#include "utils.h"

using namespace std;
using namespace Wt;

MainPage::MainPage(dbo::Session& session) :
        WTemplate(tr("main-template")), m_session(session) {
    dbo::Transaction t(m_session);
    auto citizensWidget = make_unique<WContainerWidget>();
    auto citizens = m_session.find<Citizen>().orderBy("username asc").resultList();
    bindInt("citizens_count", citizens.size());
    for (auto& citizen : citizens) {
        auto citizenRow = citizensWidget->addNew<WTemplate>(tr("citizen-row"));
        citizenRow->bindString("fullname", citizen->fullname);
        citizenRow->bindString("pageurl", PAGEURL(citizen->username));
    }
    bindWidget("citizens", move(citizensWidget));
    bindNew<TweetsContainer>("tweets", m_session);
}
