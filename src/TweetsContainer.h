/*
 * TweetContainer.h
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#ifndef TWEETSCONTAINER_H_
#define TWEETSCONTAINER_H_

#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class TweetsContainer: public Wt::WContainerWidget {
public:
	TweetsContainer(dbo::Session &session, const Wt::WString& name = "");
};

#endif /* TWEETSCONTAINER_H_ */
