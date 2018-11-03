/*
 * MainPage.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef MAINPAGE_H_
#define MAINPAGE_H_

#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class MainPage: public Wt::WTemplate {
private:
	dbo::Session& m_session;
public:
	MainPage(dbo::Session& session);
};

#endif /* MAINPAGE_H_ */
