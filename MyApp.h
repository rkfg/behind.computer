/*
 * Application.h
 *
 *  Created on: 11 Aug 2016
 *      Author: rkfg
 */

#ifndef MYAPP_H_
#define MYAPP_H_

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/MySQL>
#include "Post.h"

using namespace Wt;
namespace dbo = Wt::Dbo;

class MyApp: public WApplication {
private:
	dbo::Session& m_session;
public:
	MyApp(const WEnvironment& env, dbo::Session& session, Post& post);
};

#endif /* MYAPP_H_ */
