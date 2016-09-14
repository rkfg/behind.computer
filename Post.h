/*
 * Post.h
 *
 *  Created on: 22 Aug 2016
 *      Author: rkfg
 */

#ifndef TEMPLATES_POST_H_
#define TEMPLATES_POST_H_

#include <Wt/WResource>

using namespace Wt;
using namespace std;

namespace dbo = Wt::Dbo;

class Post: public WResource {
private:
	const string PASSWORD = "***";
	dbo::Session& m_session;
public:
	Signal<> reloadPosts;
	Post(dbo::Session& session);
	void handleRequest(const Http::Request& request, Http::Response& response);
	virtual ~Post();
};

#endif /* TEMPLATES_POST_H_ */
