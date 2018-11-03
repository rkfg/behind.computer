/*
 * Application.h
 *
 *  Created on: 11 Aug 2016
 *      Author: rkfg
 */

#ifndef MYAPP_H_
#define MYAPP_H_

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/MySQL.h>
#include "Post.h"

namespace dbo = Wt::Dbo;

class MyApp: public Wt::WApplication {
private:
	dbo::Session& m_session;
public:
	MyApp(const Wt::WEnvironment& env, dbo::Session& session, Post& post);
};

#endif /* MYAPP_H_ */
