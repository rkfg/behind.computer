/*
 * TweetWidget.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: rkfg
 */

#include "TweetWidget.h"
#include <Wt/WDateTime>
#include "domain/Citizen.h"
#include <boost/regex.hpp>

TweetWidget::TweetWidget(const Tweet& tweet, WContainerWidget* parent) :
		WTemplate(tr("tweet-template"), parent) {
	setStyleClass("tweet");
	bindString("username", tweet.citizen->username);
	bindString("fullname", tweet.citizen->fullname);
	bindString("text",
			WString::fromUTF8(
					boost::regex_replace(tweet.text.toUTF8(),
							boost::regex("(https?://\\S+)"),
							"<a href=\"$1\" target=\"_blank\">$1</a>")));
	bindString("date", tweet.date.toString("dd.MM.yyyy HH:mm:ss"));
}