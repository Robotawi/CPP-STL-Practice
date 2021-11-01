#include "json.hpp"
#include <curl/curl.h>
#include <memory>
#include <functional>

//make curl object c++11 friendly (lines 16 - 28)
//curl and smart pointers are not compatible
//we need a custom deleter function as a lambda function below \
and in the class

typedef std::unique_ptr<CURL, std::function<void(CURL *)>> CURL_ptr;

class CurlHandle
{
private:
    CURL_ptr curlptr;
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
    }

    void setUrl(std::string url)
    {
        curl_easy_setopt(curlptr.get(), CURLOPT_URL, url.c_str());
    }

    CURLcode fetch()
    {
        return curl_easy_perform(curlptr.get());
    }
};

class Bitcoin
{
    private:
    CurlHandle curlHandle; 
    static constexpr const char* API_URL="https://blockchain.info/ticker"; 

    public:
    Bitcoin(): curlHandle({}){
        curlHandle.setUrl(API_URL); 
    }

    void fetchBitcoinData(){
        curlHandle.fetch(); 
    }

};

int main(int argc, char const *argv[])
{
    /* code */
    Bitcoin mybtcoin; 
    mybtcoin.fetchBitcoinData(); 
    return 0;
}
