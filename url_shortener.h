#ifndef URL_SHORTENER_H
#define URL_SHORTENER_H

#include <string>
#include <unordered_map>

class URLShortener {

private:
    std::unordered_map<std::string, std::string> codeToUrl;
    std::unordered_map<std::string, std::string> urlToCode;
    std::unordered_map<std::string, int> clicks;

public:
    URLShortener();

    std::string shorten(std::string url);
    std::string redirect(std::string code);
    int getClicks(std::string code);   // ADD THIS LINE
};

#endif