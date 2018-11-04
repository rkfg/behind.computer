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
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/Query.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/Transaction.h>
#include <Wt/WString.h>

#include "domain/Citizen.h"
#include "TweetsContainer.h"

using namespace boost::filesystem;
using namespace std;
using namespace Wt;

PersonalPage::PersonalPage(dbo::Session& session, const WString& hostName) :
        WTemplate(tr("personal-template")), m_session(session), m_hostName(hostName) {
    dbo::Transaction t(session);
    int imgCount = 0;
    bindString("host", hostName);
    try {
        auto citizen = session.find<Citizen>().where("username = ?").bind(hostName).resultValue();
        if (citizen) {
            bindString("fullname", citizen->fullname);
            reload();
            path galPath("/srv/behind.computer/gal");
            galPath.append(hostName.toUTF8());
            auto imgs = bindWidget("imgs", make_unique<WContainerWidget>());
            for (auto i = directory_iterator(galPath); i != directory_iterator(); i++) {
                if (!is_directory(i->path())) {
                    auto imgTempl = imgs->addNew<WTemplate>(tr("gal-img"));
                    imgTempl->setInline(true);
                    imgTempl->bindString("host", hostName);
                    imgTempl->bindString("img", i->path().filename().string());
                }
            }
            imgCount = imgs->count();
            doJavaScript("$(document).ready(function() {$(\".fancybox\").fancybox();});");
        } else {
            setTemplateText(tr("not-found"));
        }
    } catch (exception& e) {
        log("warn") << "Error showing personal page of user " << hostName << ": " << e.what();
    }
    log("info") << "Img count " << imgCount;
    if (!imgCount) {
        setTemplateText(tr("non-legit"));
    }
}

void PersonalPage::reload() {
    bindNew<TweetsContainer>("tweets", m_session, m_hostName);
}
