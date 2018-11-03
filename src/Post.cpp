/*
 * Post.cpp
 *
 *  Created on: 22 Aug 2016
 *      Author: rkfg
 */

#include "Post.h"

#include <iostream>
#include <string>
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>
#include <Wt/WDateTime.h>
#include <Wt/WLogger.h>

#include "domain/Citizen.h"
#include "domain/Tweet.h"

using namespace Wt;
using namespace std;

Post::Post(dbo::Session& session) :
		m_session(session) {
}

void Post::handleRequest(const Http::Request& request,
		Http::Response& response) {
	if (request.method() != "POST") {
		return;
	}
	auto passwd = request.getParameter("passwd");
	response.setMimeType("text/html");
	if (!passwd || *passwd != PASSWORD) {
		response.setStatus(401);
		response.out() << "Invalid password.";
		return;
	}
	auto from = request.getParameter("from");
	auto text = request.getParameter("text");
	if (!from || !text) {
		response.setStatus(400);
		response.out() << "Not all parameters set.";
		return;
	}
	try {
		dbo::Transaction t(m_session);
		auto citizen = m_session.find<Citizen>().where("username = ?").bind(
				*from).resultValue();
		if (!citizen) {
			response.setStatus(404);
			response.out() << "Citizen " << *from << " not found.";
			return;
		}
		auto tweet = make_unique<Tweet>();
		tweet->citizen = citizen;
		tweet->date = WDateTime::currentDateTime();
		tweet->text = WString::fromUTF8(*text);
		m_session.add(move(tweet));
		log("info") << "Added tweet from " << *from << " text: " << *text;
	} catch (exception& e) {
		log("warn") << "Error sending post from " << *from << ": " << e.what();
		response.setStatus(500);
		response.out() << "Internal server error.";
		return;
	}
	response.setStatus(200);
	response.out() << "ok";
	reloadPosts.emit();
}

Post::~Post() {
	beingDeleted();
}
