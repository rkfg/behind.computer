/*
 * TweetContainer.h
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#ifndef TWEETSCONTAINER_H_
#define TWEETSCONTAINER_H_

#include <Wt/WContainerWidget>
#include <Wt/Dbo/Dbo>

using namespace Wt;
namespace dbo = Wt::Dbo;

class TweetsContainer: public WContainerWidget {
public:
	TweetsContainer(dbo::Session &session, const WString& name = "",
			WContainerWidget* parent = 0);
};

#endif /* TWEETSCONTAINER_H_ */
