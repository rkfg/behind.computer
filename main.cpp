/*
 * main.cpp
 *
 *  Created on: 11 Aug 2016
 *      Author: rkfg
 */

#include <signal.h>
#include <unistd.h>
#include <Wt/WConfig.h>
#include <iostream>
#include <Wt/Dbo/backend/MySQL>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/FixedSqlConnectionPool>
#include <Wt/WEnvironment>
#include <Wt/WGlobal>
#include <Wt/WServer>

#include "domain/Citizen.h"
#include "domain/Tweet.h"
#include "MyApp.h"
#include "Post.h"

using namespace std;
using namespace Wt;
namespace dbo = Wt::Dbo;

WApplication* createApp(const WEnvironment& env, dbo::Session& session, Post& post) {
	return new MyApp(env, session, post);
}

int main(int argc, char* argv[]) {
	try {
		dbo::backend::MySQL* conn = new dbo::backend::MySQL("bc", "bc", "***", "127.0.0.1", 3306);
		dbo::FixedSqlConnectionPool pool(conn, 10);
		dbo::Session session;
		session.setConnectionPool(pool);
		session.mapClass<Citizen>("citizen");
		session.mapClass<Tweet>("tweet");
		try {
			dbo::Transaction t(session);
			session.createTables();
		} catch (exception& e) {
			log("info") << "Error: " << e.what();
		}
		WServer server(argv[0]);
		server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
		Post* post = new Post(session);
		server.addResource(post, "/post");
		server.addEntryPoint(Wt::Application, bind(createApp, _1, ref(session), ref(*post)));
		if (server.start()) {
			int sig = WServer::waitForShutdown(argv[0]);
			std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
			server.stop();
			if (sig == SIGHUP)
				WServer::restart(argc, argv, environ);
		}
	} catch (const WServer::Exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	} catch (const std::exception& e) {
		std::cerr << "exception: " << e.what() << "\n";
		return 1;
	}
}
