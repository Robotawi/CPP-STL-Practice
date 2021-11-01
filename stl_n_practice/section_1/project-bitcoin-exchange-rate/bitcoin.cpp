#include "json.hpp"
#include <curl/curl.h>
#include <memory>
#include <functional>
#include <iostream>

//args are required for any function writer that uses curl
extern "C" std::size_t dataHandler(const char *buffer, std::size_t size,
                                   std::size_t numMemb, std::string *userData)
{
    if (userData == nullptr)
    {
        return 0;
    }

    userData->append(buffer, (size * numMemb));
    return size * numMemb;
}

//make curl object c++11 friendly (lines 16 - 28)
//curl and smart pointers are not compatible
//we need a custom deleter function as a lambda function below \
and in the class

typedef std::unique_ptr<CURL, std::function<void(CURL *)>> CURL_ptr;

class CurlHandle
{
private:
    CURL_ptr curlptr;
    std::string data;
    constexpr static auto deleter = [](CURL *c)
    {
        curl_easy_cleanup(c);
        curl_global_cleanup();
    };

public:
    //construct and init the member curlptr
    CurlHandle() : curlptr(curl_easy_init(), deleter)
    {
        curl_global_init(CURL_GLOBAL_ALL); //init all needed memory
        curl_easy_setopt(curlptr.get(), CURLOPT_WRITEFUNCTION, dataHandler);
        curl_easy_setopt(curlptr.get(), CURLOPT_WRITEDATA, &data);
    }

    void setUrl(std::string url)
    {
        curl_easy_setopt(curlptr.get(), CURLOPT_URL, url.c_str());
    }

    CURLcode fetch()
    {
        return curl_easy_perform(curlptr.get());
    }

    std::string getFetchData()
    {
        return data;
    }
};

class Bitcoin
{
    using json = nlohmann::json;

private:
    CurlHandle curlHandle;
    static constexpr const char *API_URL = "https://blockchain.info/ticker";

public:
    Bitcoin() : curlHandle({})
    {
        curlHandle.setUrl(API_URL);
    }

    //make it return a json parsed object
    json fetchBitcoinData()
    {
        curlHandle.fetch();
        return json::parse(curlHandle.getFetchData());
    }
};

int main(int argc, char const *argv[])
{   //notice: using beings namespace to only main scope
    //the same for json to be nlohmann::json to be called json in name scope
    using namespace std;
    using json = nlohmann::json;
    try
    {
        Bitcoin mybitcoin;
        json bitcoinData = mybitcoin.fetchBitcoinData();

        cout << "1 BTC = \n";
        for (auto it = bitcoinData.begin(); it != bitcoinData.end(); it++)
        {
            printf("\t(%3s)%10d %s \n", it.key().c_str(),
                   it.value()["last"].get<int>(), it.value()["symbol"].get<string>().c_str());
        }
    }
    catch (...)
    {
        cerr << "Failed to fetch bitcoin exchange rates.\n";
    }
}
