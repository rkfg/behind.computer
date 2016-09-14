/*
 * TweetWidget.h
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#ifndef TWEETWIDGET_H_
#define TWEETWIDGET_H_

#include <Wt/WTemplate>
#include "domain/Tweet.h"

using namespace Wt;

class TweetWidget: public WTemplate {
public:
	TweetWidget(const Tweet& tweet, WContainerWidget* parent = 0);
};

#endif /* TWEETWIDGET_H_ */
