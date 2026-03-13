#include "url_shortener.h"
#include <iostream>
#include <fstream>

using namespace std;

static int id = 1;

string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


// Base62 encoding function
string encode(int num) {

    string code = "";

    while(num > 0) {
        code += chars[num % 62];
        num /= 62;
    }

    return code;
}


// Constructor: load existing URLs from database.txt
URLShortener::URLShortener() {

    ifstream file("database.txt");

    string code, url;
    int clickCount;

    while(file >> code >> url >> clickCount) {

        codeToUrl[code] = url;
        urlToCode[url] = code;
        clicks[code] = clickCount;

        id++;  // move id forward to avoid collisions
    }

    file.close();
}


// Shorten URL
string URLShortener::shorten(string url) {

    // prevent duplicate short URLs
    if(urlToCode.find(url) != urlToCode.end()) {
        return urlToCode[url];
    }

    string code = encode(id);

    codeToUrl[code] = url;
    urlToCode[url] = code;
    clicks[code] = 0;

    // save to database
    ofstream file("database.txt", ios::app);
    file << code << " " << url << " " << 0 << endl;
    file.close();

    id++;

    return code;
}


// Redirect short URL
string URLShortener::redirect(string code) {

    if(codeToUrl.find(code) != codeToUrl.end()) {

        clicks[code]++;
        cout << "DEBUG clicks: " << clicks[code] << endl;

        return codeToUrl[code];
    }

    return "URL not found";
}

int URLShortener::getClicks(string code) {

    auto it = clicks.find(code);

    if(it != clicks.end()) {
        return it->second;
    }

    return -1;
}
