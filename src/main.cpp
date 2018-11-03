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

#include <boost/program_options.hpp>

#include "domain/Citizen.h"
#include "domain/Tweet.h"
#include "MyApp.h"
#include "Post.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {
        po::options_description od;
        od.add_options()("db_name", po::value<std::string>()->default_value("bc")->required())("db_username",
                po::value<std::string>()->default_value("bc")->required())("db_password",
                po::value<std::string>()->required())("db_hostname",
                po::value<std::string>()->default_value("127.0.0.1")->required())("db_port",
                po::value<unsigned short>()->default_value(3306)->required())("post_password",
                po::value<std::string>()->required());
        po::variables_map vm;
        try {
            po::store(po::parse_config_file<char>("settings.ini", od), vm);
            vm.notify();
        } catch (const po::error& e) {
            Wt::log("error") << "Error parsing settings.ini: " << e.what();
            return 1;
        }
        dbo::FixedSqlConnectionPool pool(
                std::make_unique<dbo::backend::MySQL>(vm["db_name"].as<std::string>(),
                        vm["db_username"].as<std::string>(), vm["db_password"].as<std::string>(),
                        vm["db_hostname"].as<std::string>(), vm["db_port"].as<unsigned short>()), 10);
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
        Wt::WServer server(argc, argv);
        Post post(session, vm["post_password"].as<std::string>());
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
