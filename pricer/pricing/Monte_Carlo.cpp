#include "Monte_Carlo.h"

#include <math.h>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <vector>
#include <type_traits>
#include <typeinfo>

#include "../derivatives/Derivative.h"
#include "../derivatives/Non_Path_Dependant.h"
#include "../derivatives/Path_Dependant.h"

using namespace std;
using namespace derivatives;

namespace pricers
{
    double Monte_Carlo::price(Derivative* derivative, int nbr_simulations,
        int nbr_steps)
    {
        // Parameters from the derivative
        double s0 = derivative->get_s0();
        double sigma = derivative->get_sigma();
        double r = derivative->get_r();

        // Parameters for the simulation
        double sum_simulations = 0;
        double dt = derivative->get_t()/nbr_steps;
        double drift = (r - 0.5*pow(sigma, 2))*dt;
        double volatility = sigma*sqrt(dt);

        // Initializing the random generator
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        normal_distribution<double> norm_dist(0, 1);

        // First we try to check if it is a non path dependant derivative
        // Dynamic cast in order to get the payoff function
        Non_Path_Dependant* child_derivative =
            dynamic_cast<Non_Path_Dependant*>(derivative);
        if(child_derivative != NULL)
        {
            // No need to store in a vector since it is not path dependant
            // We are only interested in the final value
            for(int i=0; i<nbr_simulations; i++)
            {
                double simulated_price = s0;

                for(int j = 0; j < nbr_steps; j++)
                {
                    simulated_price *= exp(drift+
                                        volatility*norm_dist(generator));
                }
                // Calling the payoff function of the child
                sum_simulations += child_derivative->payoff(simulated_price);
            }
        }
        /* If it is not a non path dependant derivative, we then check if
           it is a path dependant derivative */
        else
        {
            // Dynamic cast in order to get the payoff function
            Path_Dependant* child_derivative =
                dynamic_cast<Path_Dependant*>(derivative);
            if(child_derivative != NULL)
            {
                /* For a path dependant derivative, we need to store each
                   state in memory in a vector */
                for(int i=0; i<nbr_simulations; i++)
                {
                    vector<double> simulated_prices(nbr_steps);
                    simulated_prices[0] = s0;

                    for(int j = 1; j < nbr_steps; j++)
                    {
                        simulated_prices[j] = simulated_prices[j-1]*
                                            exp(drift+
                                            volatility*norm_dist(generator));
                    }

                    // Calling the payoff function of the child
                    sum_simulations +=
                        child_derivative->payoff(simulated_prices);

                }
            }
            /* If the derivative is neither non path dependant nor path
               dependant, it is not a valid parameter */
            else
            {
                return -1;
            }
        }
        // Returning the mean of all simulations
        return sum_simulations/nbr_simulations;
    }
}
