/*
 * Application.cpp
 *
 *  Created on: 11 Aug 2016
 *      Author: rkfg
 */

#include "MyApp.h"

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <Wt/WBootstrapTheme>
#include <Wt/WEnvironment>

#include "MainPage.h"
#include "PersonalPage.h"

using namespace std;

MyApp::MyApp(const WEnvironment& env, dbo::Session& session, Post& post) :
		WApplication(env), m_session(session) {
	messageResourceBundle().use(appRoot() + "templates/main");
	useStyleSheet(appRoot() + "css/style.css");
	requireJQuery("https://code.jquery.com/jquery-latest.min.js");
	useStyleSheet("/fancybox/source/jquery.fancybox.css?v=2.1.5");
	require("/fancybox/source/jquery.fancybox.pack.js?v=2.1.5");
	require("/fancybox/lib/jquery.mousewheel-3.0.6.pack.js");
	setTitle(WString::tr("title"));
	setTheme(new WBootstrapTheme());
	auto hostName = env.hostName();
	vector<string> elems;
	boost::split(elems, hostName, boost::is_any_of(":"));
	if (elems.size() > 1) {
		hostName = elems[0];
	}
	log("info") << "We're at " << hostName;
	if (boost::ends_with(hostName, ".behind.computer")) {
		auto domain = boost::regex_replace(hostName,
				boost::regex("^([a-z0-9-]+)\\.behind\\.computer"), "$1");
		if (!domain.empty()) {
			log("info") << "On subdomain: " << domain;
			auto personalPage = new PersonalPage(session, WString::fromUTF8(domain), root());
			//post.reloadPosts.connect(personalPage, &PersonalPage::reload);
			return;
		}
	}
	auto mainPage = new MainPage(session, root());
	//post.reloadPosts.connect(mainPage, &MainPage::reload);
}
