/*
 * MainPage.h
 *
 *  Created on: 19 Aug 2016
 *      Author: rkfg
 */

#ifndef MAINPAGE_H_
#define MAINPAGE_H_

#include <Wt/WTemplate>
#include <Wt/WContainerWidget>
#include <Wt/Dbo/Dbo>

using namespace Wt;
namespace dbo = Wt::Dbo;

class MainPage: public WTemplate {
private:
	dbo::Session& m_session;
public:
	void reload();
	MainPage(dbo::Session& session, WContainerWidget* parent = 0);
};

#endif /* MAINPAGE_H_ */
