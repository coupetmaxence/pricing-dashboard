#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <chrono>
#include <ctime>

#include "derivatives/Derivative.h"
#include "derivatives/European_Option.h"
#include "derivatives/Asian_Option.h"
#include "tools/json.hpp"
#include "pricing/Monte_Carlo.h"

using namespace std;
using namespace std::chrono;
using namespace pricers;
using namespace derivatives;
using json = nlohmann::json;


int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        const int NBR_THREADS = 100;
        const int NBR_SIMULATIONS = 100000;
        const int NBR_STEPS = 100;

        Derivative* option = new Asian_Option(Call, 40, 40, 1, 0.2, 0.01, 0, 0);


        vector<packaged_task<double(Derivative*,int,int)>> tasks(NBR_THREADS);
        vector<future<double>> values(NBR_THREADS);
        vector<thread> threads(NBR_THREADS);

        // Creating promises
        for(unsigned int i = 0; i < threads.size(); i++)
        {
            tasks[i] = packaged_task<double(Derivative*,int,int)> (
                Monte_Carlo::price);
        }

        // Get futures
        for(unsigned int i = 0; i < threads.size(); i++)
        {
            values[i] = tasks[i].get_future();
        }

        // Schedule promises
        for(unsigned int i = 0; i < threads.size(); i++)
        {
            threads[i] = thread(move(tasks[i]),
                            option, NBR_SIMULATIONS/NBR_THREADS, NBR_STEPS);
        }

        // Waiting for every thread to finish its task
        for(unsigned int i = 0; i < threads.size(); i++)
        {
            threads[i].join();
        }

        double option_price = 0;
        for(unsigned int i = 0; i < threads.size(); i++)
        {
            option_price += values[i].get();
        }

        // Creating the json standard output
        json response;

        time_t time_actual = time(nullptr);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(t2-t1).count();
        response["meta"] = {
            {"status", "success"},
            {"timestamp", asctime(localtime(&time_actual))},
            {"calculation_time", duration},
            {"user", "ed43f5ea5d"}
        };
        response["data"] = {
            {"price", option_price/NBR_THREADS}
        };


        cout << response.dump();
    }
    else
    {
        // Creating the json standard output
        json error_json;
        time_t time_actual = time(nullptr);
        error_json["meta"] = {
            {"status", "error"},
            {"timestamp", asctime(localtime(&time_actual))}
        };
        error_json["data"] = {
        };

        cout << error_json.dump();
    }

    return 0;
}
