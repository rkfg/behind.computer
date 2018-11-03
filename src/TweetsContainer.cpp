/*
 * TweetContainer.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#include "TweetsContainer.h"
#include "TweetWidget.h"
#include "domain/Tweet.h"
#include <Wt/Dbo/WtSqlTraits.h>

using namespace Wt;
using namespace std;

TweetsContainer::TweetsContainer(dbo::Session &session, const WString& username) {
    try {
        dbo::Transaction t(session);
        auto query = session.query<dbo::ptr<Tweet>>(
                string("select t from tweet t left join citizen c on t.citizen_id = c.id"));
        if (username.empty()) {
            query.orderBy("date desc");
        } else {
            query.where("c.username = ?").bind(username);
        }
        auto tweets = query.limit(20).orderBy("date desc").resultList();
        for (auto& tweet : tweets) {
            addNew<TweetWidget>(*tweet);
        }
    } catch (exception& e) {
        log("warn") << "Error loading tweets of user " << username << ": " << e.what();
    }
}
