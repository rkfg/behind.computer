/*
 * main.cpp
 *
 *  Created on: 11 Aug 2016
 *      Author: rkfg
 */

#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <Wt/WConfig.h>
#include <Wt/Dbo/backend/MySQL.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/FixedSqlConnectionPool.h>
#include <Wt/WEnvironment.h>
#include <Wt/WGlobal.h>
#include <Wt/WServer.h>

#include "domain/Citizen.h"
#include "domain/Tweet.h"
#include "MyApp.h"
#include "Post.h"

int main(int argc, char* argv[]) {
    try {
        dbo::FixedSqlConnectionPool pool(
                std::make_unique<dbo::backend::MySQL>("bc", "bc", "***", "127.0.0.1", 3306), 10);
        dbo::Session session;
        session.setConnectionPool(pool);
        session.mapClass<Citizen>("citizen");
        session.mapClass<Tweet>("tweet");
        try {
            dbo::Transaction t(session);
            session.createTables();
        } catch (std::exception& e) {
            Wt::log("info") << "Error: " << e.what();
        }
        Wt::WServer server(argv[0]);
        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        Post post(session);
        server.addResource(&post, "/post");
        server.addEntryPoint(Wt::EntryPointType::Application, [&](const Wt::WEnvironment& env) {
            return std::make_unique<MyApp>(env, session, post);
        });
        if (server.start()) {
            int sig = Wt::WServer::waitForShutdown();
            Wt::log("warn") << "Shutdown (signal = " << sig << ")";
            server.stop();
            if (sig == SIGHUP)
                Wt::WServer::restart(argc, argv, environ);
        }
    } catch (const Wt::WServer::Exception& e) {
        std::cerr << "WServer exception: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << "\n";
        return 1;
    }
}
