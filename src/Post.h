/*
 * Post.h
 *
 *  Created on: 22 Aug 2016
 *      Author: rkfg
 */

#ifndef TEMPLATES_POST_H_
#define TEMPLATES_POST_H_

#include <Wt/WResource.h>

namespace dbo = Wt::Dbo;

class Post: public Wt::WResource {
private:
	const std::string PASSWORD = "***";
	dbo::Session& m_session;
public:
	Wt::Signal<> reloadPosts;
	Post(dbo::Session& session);
	void handleRequest(const Wt::Http::Request& request, Wt::Http::Response& response);
	~Post();
};

#endif /* TEMPLATES_POST_H_ */
