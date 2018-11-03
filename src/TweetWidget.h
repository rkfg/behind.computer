/*
 * TweetWidget.h
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#ifndef TWEETWIDGET_H_
#define TWEETWIDGET_H_

#include <Wt/WTemplate.h>
#include "domain/Tweet.h"

class TweetWidget: public Wt::WTemplate {
public:
	TweetWidget(const Tweet& tweet);
};

#endif /* TWEETWIDGET_H_ */
