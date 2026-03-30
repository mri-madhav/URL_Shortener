#include "crow/crow.h"
#include "url_shortener.h"

URLShortener shortener;

void startServer() {

    crow::SimpleApp app;

    // shorten URL
    CROW_ROUTE(app, "/shorten")
    .methods("POST"_method)
    ([](const crow::request& req){

        auto url = req.body;

        std::string code = shortener.shorten(url);

        return "short.ly/" + code;
    });

    // redirect
    CROW_ROUTE(app, "/<string>")
    ([](std::string code){

        std::string url = shortener.redirect(code);

        crow::response res;
        res.code = 302;
        res.set_header("Location", url);

        return res;
    });

    app.port(18080).multithreaded().run();
}