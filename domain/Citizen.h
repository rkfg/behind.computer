/*
 * Citizen.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef DOMAIN_CITIZEN_H_
#define DOMAIN_CITIZEN_H_

#include <Wt/Dbo/Dbo>
#include <Wt/WString>
#include <Wt/Dbo/WtSqlTraits>

namespace dbo = Wt::Dbo;
using namespace std;
using namespace Wt;

class Tweet;

class Citizen {
public:
	WString username;
	WString fullname;
	dbo::collection<dbo::ptr<Tweet>> tweets;
	Citizen();
	template<typename Action> void persist(Action& a) {
		dbo::field(a, username, "username");
		dbo::field(a, fullname, "fullname");
		dbo::hasMany(a, tweets, dbo::ManyToOne);
	}
};

#endif /* DOMAIN_CITIZEN_H_ */
