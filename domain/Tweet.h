/*
 * Tweet.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef DOMAIN_TWEET_H_
#define DOMAIN_TWEET_H_

#include <Wt/Dbo/Dbo>
#include <Wt/WString>
#include <Wt/WDateTime>

namespace dbo = Wt::Dbo;
using namespace std;
using namespace Wt;

class Citizen;

class Tweet {
public:
	WDateTime date;
	WString text;
	dbo::ptr<Citizen> citizen;
	Tweet();
	template<typename Action> void persist(Action& a){
		dbo::field(a, date, "date");
		dbo::field(a, text, "text");
		dbo::belongsTo(a, citizen);
	}
};

#endif /* DOMAIN_TWEET_H_ */
