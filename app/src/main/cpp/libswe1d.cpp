

#include <string>
#include <fenv.h>


#include "Source/Scenarios/DamBreakScenario.hpp"
#include "Source/Scenarios/ShockShockScenario.hpp"
#include "Source/Scenarios/RareRareScenario.hpp"
#include "Source/Scenarios/SubcriticalFlowScenario.hpp"
#include "Source/Scenarios/SupercriticalFlowScenario.hpp"
//#include "Source/Tools/Args.hpp"
#include "Source/Tools/RealType.hpp"
//#include "Source/Writers/ConsoleWriter.hpp"
#include "Source/Tools/RealType.hpp"
#include "Source/Blocks/WavePropagationBlock_1D.hpp"
#include "Source/Writers/VTKSWE1DWriter.hpp"

#include <jni.h>
#include <string>
#include <iostream>

std::string
runner_main(const std::string &scenario, int size, int time_step, const std::string &dir_name);

std::string jstring2string(JNIEnv *env, jstring jStr);
Scenarios::Scenario1D *getScenarioBasedOnName(const std::string &name, int domain_size);


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_cppdemo_SWE1D_main(JNIEnv *env, jobject thiz, jstring scenario, jint size,
                                    jint time_step, jstring dir) {
    std::string dir_name = jstring2string(env, dir);
    std::string scenario_name = jstring2string(env, scenario);
    return env->NewStringUTF(runner_main(scenario_name, size, time_step, dir_name).c_str());
}

double createRandomNumber_MAIN(double min, double max);

std::string runner_main(const std::string &scenario_name, int size, int time_step,
                        const std::string &dir_name) {
    // Triggers signals on floating point errors, i.e. prohibits quiet NaNs and alike.
    // feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW); causes SWE1D to stop


    std::stringstream output;
    //unsigned int domain_size = 24;// for sub/supercritical
    unsigned int domain_size = size;// for other scenarios

    // Scenario
    auto &scenario = *getScenarioBasedOnName(scenario_name, domain_size);

    // Allocate memory
    // Water height
    auto *h = new RealType[domain_size + 2];
    // Momentum
    auto *hu = new RealType[domain_size + 2];
    // Bathymetry
    auto *b = new RealType[domain_size + 2];


    //todo option: randomized bathymetry
    //for dam/shock/rare scenarios
    for (unsigned int i = 0; i < domain_size + 2; i++) {
        //b[i] = scenario.getBathymetry(i);// for sub/super

        //for other scenarios, feel free to set any range (x, y)
        //with x < 0, otherwise meaningless: no water, every cell is dry
        //std::cout << "domainsize: " <<domain_size <<" "<< i <<std::endl;
        // if(i == domain_size){
        //   b[i] = 100;
        // }
        //Note: b[i] must be set to a valid number, otherwise it will cause undefined behavior

        //comment this out if you want some random bathymetry in the domain       b[i] = createRandomNumber_MAIN(-2, -1);
        b[i] = 0; //no bathymetry at all

        h[i] = scenario.getHeight(i);//for shockshock and rarerare
        hu[i] = scenario.getMomentum(i);//applys to all scenarios
    }

    std::string absolute_path = "/sdcard/" + dir_name + "/";

    // Create a writer that is responsible printing out values
    Writers::VTKSWE1DWriter vtkSwe1dWriter(absolute_path + "SWE1D", scenario.getCellSize());

    // Helper class computing the wave propagation
    Blocks::WavePropagationBlock_1D wavePropagation(h, hu, b, domain_size, scenario.getCellSize());

    // Write initial data

    // Current time of simulation
    double t = 0;
    vtkSwe1dWriter.write(t, h, hu, domain_size);

    for (unsigned int i = 0; i < time_step; i++) {
        // Do one time step

        // Update boundaries
        wavePropagation.setOutflowBoundaryConditions();

        // Compute numerical flux on each edge
        RealType maxTimeStep = wavePropagation.computeNumericalFluxes();

        // Update unknowns from net updates
        wavePropagation.updateUnknowns(maxTimeStep);

        output << "Computing iteration " << i << " at time " << t << " with max. timestep "
               << maxTimeStep << std::endl;

        // Update time
        t += maxTimeStep;

        // Write new values
        //consoleWriter.write(h, hu, domain_size);
        vtkSwe1dWriter.write(t, h, hu, domain_size);

    }

    // Free allocated memory
    delete[] h;
    delete[] hu;
    std::ofstream output_text(absolute_path + "output.txt");
    output_text << output.str();
    return output.str();
}

double createRandomNumber_MAIN(const double min, const double max) {
    double randomNumber = ((double) rand() / (double) RAND_MAX);
    return min + (max - min) * randomNumber;
}

Scenarios::Scenario1D *getScenarioBasedOnName(const std::string &name, int domain_size) {
    if (name == "DamBreakScenario") {
        auto *scenario = new Scenarios::DamBreakScenario(domain_size);
        return scenario;
    } else if (name == "ShockShockScenario") {
        auto *scenario = new Scenarios::ShockShockScenario(10, 10, 50);
        return scenario;
    } else if (name == "RareRareScenario") {
        auto *scenario = new Scenarios::RareRareScenario(10, -10, 50);
        return scenario;
    } else if (name == "SubcriticalScenario") {
        auto *scenario = new Scenarios::SubcriticalFlowScenario;
        return scenario;
    } else {
        auto *scenario = new Scenarios::SupercriticalFlowScenario;
        return scenario;
    }
}


