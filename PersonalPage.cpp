/*
 * PersonalPage.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#include "PersonalPage.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <Wt/Dbo/Query_impl.h>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/Query>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/Transaction>
#include <Wt/WString>

#include "domain/Citizen.h"
#include "TweetsContainer.h"

using namespace boost::filesystem;

PersonalPage::PersonalPage(dbo::Session& session, const WString& hostName,
		WContainerWidget* parent) :
		WTemplate(tr("personal-template"), parent), m_session(session), m_hostName(
				hostName) {
	dbo::Transaction t(session);
	try {
		auto citizen = session.find<Citizen>().where("username = ?").bind(
				hostName).resultValue();
		if (citizen) {
			bindString("fullname", citizen->fullname);
			reload();
			path galPath("/srv/behind.computer/gal");
			galPath.append(hostName.toUTF8());
			auto imgs = new WContainerWidget();
			bindWidget("imgs", imgs);
			for (auto i = directory_iterator(galPath);
					i != directory_iterator(); i++) {
				if (!is_directory(i->path())) {
					auto imgTempl = new WTemplate(tr("gal-img"));
					imgTempl->setInline(true);
					imgTempl->bindString("host", hostName);
					imgTempl->bindString("img", i->path().filename().string());
					imgs->addWidget(imgTempl);
				}
			}
			doJavaScript(
					"$(document).ready(function() {$(\".fancybox\").fancybox();});");
		} else {
			setTemplateText(tr("not-found"));
			bindString("host", hostName);
		}
	} catch (exception& e) {
		log("warn") << "Error showing personal page of user " << hostName
				<< ": " << e.what();
	}
}

void PersonalPage::reload() {
	bindWidget("tweets", new TweetsContainer(m_session, m_hostName));
}
