#include <iostream>
#include "server.h"
#include "url_shortener.h"

using namespace std;

void startServer() {

    URLShortener shortener;

    while(true) {

        cout << "\n===== URL Shortener =====\n";
        cout << "1. Shorten URL\n";
        cout << "2. Open Short URL\n";
        cout << "3. View Click Analytics\n";
        cout << "4. Exit\n";

        int choice;
        cin >> choice;

        if(choice == 1) {

            string url;
            cout << "Enter URL: ";
            getline(cin >> ws, url);

            string code = shortener.shorten(url);

            cout << "Short URL: short.ly/" << code << endl;
        }

        else if(choice == 2) {

            string code;
            cout << "Enter short code: ";
            getline(cin >> ws, code);

            string original = shortener.redirect(code);

            cout << "Redirected URL: " << original << endl;
        }

        else if(choice == 3) {

            string code;
            cout << "Enter short code: ";
            getline(cin >> ws, code);

            int count = shortener.getClicks(code);

            if(count == -1) {
                cout << "Short URL not found\n";
            }
            else {
                cout << "Total clicks for short.ly/" << code << " = " << count << endl;
            }
        }

        else if(choice == 4) {

            cout << "Exiting server...\n";
            break;
        }

        else {
            cout << "Invalid choice\n";
        }
    }
}