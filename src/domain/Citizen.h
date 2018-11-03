/*
 * Citizen.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef DOMAIN_CITIZEN_H_
#define DOMAIN_CITIZEN_H_

#include <Wt/Dbo/Dbo.h>
#include <Wt/WString.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class Tweet;

class Citizen {
public:
	Wt::WString username;
	Wt::WString fullname;
	dbo::collection<dbo::ptr<Tweet>> tweets;
	Citizen();
	template<typename Action> void persist(Action& a) {
		dbo::field(a, username, "username");
		dbo::field(a, fullname, "fullname");
		dbo::hasMany(a, tweets, dbo::ManyToOne);
	}
};

#endif /* DOMAIN_CITIZEN_H_ */
