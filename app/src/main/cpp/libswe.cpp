#include <jni.h>
#include <string>
//#include </usr/include/netcdf.h>

#include <iostream>
#include <fstream>
#include "Source/Blocks/DimensionalSplitting.hpp"
#include "Source/Scenarios/RadialDamBreakScenario.hpp"
#include "Source/Scenarios/BathymetryDamBreakScenario.hpp"
#include "Source/Scenarios/TsunamiScenario.hpp"
#include "Source/Scenarios/ArtificialTsunamiScenario.hpp"
#include "Source/Tools/Args.hpp"
#include "Source/Writers/Writer.hpp"
#include "Source/BoundaryEdge.hpp"

std::string
runner_main(std::string &scenarioName, int domain_x, int domain_y, int checkpoints,
            const std::string &cond, std::string &baseName, const std::string &dir_name);

Scenarios::Scenario *getScenarioBasedOnName(std::string &name);

std::string jstring2string(JNIEnv *env, jstring jStr);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_cppdemo_SWE_main(JNIEnv *env, jobject thiz, jstring scenarioName, jint x, jint y,
                                  jint cp, jstring cond, jstring baseName, jstring dir) {
    std::string sname = jstring2string(env, scenarioName);
    std::string name = jstring2string(env, baseName);
    std::string dir_name = jstring2string(env, dir);
    std::string bcond = jstring2string(env, cond);

    return env->NewStringUTF(
            runner_main(
                    sname,
                    x,
                    y,
                    cp,
                    bcond,
                    name,
                    dir_name).c_str());
}

/**
 * @note:
 * an early experimental version, only switched scenario to TsunamiScenario
 * compiled and run (?) withouit error, but many bugs expected
 * */


std::string runner_main(std::string &scenarioName, int x, int y, int checkpoints,
                        const std::string &boundaryCond, std::string &baseName,
                        const std::string &dir_name) {

    std::stringstream output;

    int numberOfGridCellsX = x;
    int numberOfGridCellsY = y;
    int numberOfCheckPoints = checkpoints;

    auto &scenario = *getScenarioBasedOnName(scenarioName);

    RealType cellSize_x = (scenario.getBoundaryPos(BoundaryEdge::Right) -
                           scenario.getBoundaryPos(BoundaryEdge::Left))
                          / numberOfGridCellsX;
    RealType cellSize_y = (scenario.getBoundaryPos(BoundaryEdge::Top) -
                           scenario.getBoundaryPos(BoundaryEdge::Bottom))
                          / numberOfGridCellsY;

    auto wave_block = Blocks::Block::getBlockInstance(numberOfGridCellsX, numberOfGridCellsY,
                                                      cellSize_x, cellSize_y);
    wave_block->initialiseScenario(0, 0, scenario, false);
    // Get the final simulation time from the scenario
    double endSimulationTime = scenario.getEndSimulationTime();

    auto *checkPoints = new double[numberOfCheckPoints + 1];

    // Compute the checkpoints in time
    for (int cp = 0; cp <= numberOfCheckPoints; cp++) {
        checkPoints[cp] = cp * (endSimulationTime / numberOfCheckPoints);
    }

    // Boundary size of the ghost layers
    Writers::BoundarySize boundarySize = {{1, 1, 1, 1}};

    std::string absolute_path = "/sdcard/" + dir_name + "/";
    std::string fileName = Writers::generateBaseFileName(baseName, absolute_path, 0, 0);

    auto writer = Writers::Writer::createWriterInstance(
            fileName,
            wave_block->getBathymetry(),
            boundarySize,
            numberOfGridCellsX,
            numberOfGridCellsY,
            cellSize_x,
            cellSize_y,
            0 * 16,
            0 * 16,
            0,
            0,
            0
    );
    BoundaryType curr;
    output << "boundaryCond = " << boundaryCond << std::endl;
    //! Set boundaryTypes in Block::boundary_
    for (int i = 0; i < 4; i++) {

        if (boundaryCond.at(0) == 'W') {
            // if((boundaryCond.front()).compare('W')) {
            curr = Wall;
        } else if (boundaryCond.at(0) == 'O') {
            curr = Outflow;
        } else {
            // default/wrong parameters ==> change to default _Passive_ (block constructor also initializes as passive)
            curr = Passive;
        }
        wave_block->setBoundaryType(BoundaryEdge(i), curr);
        //boundaryCond = boundaryCond.substr(1);
    }

    // Write zero time step
    writer->writeTimeStep(wave_block->getWaterHeight(), wave_block->getDischargeHu(),
                          wave_block->getDischargeHv(), 0.0, &curr);//, nullptr);

    unsigned int iterations = 0;
    double simulationTime = 0.0;

    // Loop over checkpoints
    for (int cp = 1; cp <= numberOfCheckPoints; cp++) {
        // Do time steps until next checkpoint is reached
        while (simulationTime < checkPoints[cp]) {
            output << "running simulation at time " << simulationTime << std::endl;
            // Set values in ghost cells
            wave_block->setGhostLayer();

            // Compute numerical flux on each edge
            wave_block->computeNumericalFluxes();

            RealType maxTimeStepWidth = wave_block->getMaxTimeStep();

            // Update the cell values
            wave_block->updateUnknowns(maxTimeStepWidth);

            // Update simulation time with time step width
            simulationTime += maxTimeStepWidth;
            iterations++;
        }

        output << "new checkpoint after " << iterations << " iterations\n";
        // Write output
        writer->writeTimeStep(
                wave_block->getWaterHeight(), wave_block->getDischargeHu(),
                wave_block->getDischargeHv(), simulationTime,
                wave_block->getBoundaryType()
        );
    }


    std::ofstream output_text(absolute_path + "output.txt");
    output_text << output.str();

    // free space
    delete wave_block;
    delete &scenario;
    delete[] checkPoints;

    return output.str();
}

// To avoid object slicing, Scenario is changed to be marked as pure virtual class through making functions "=0",
// so that correct getWaterHeight etc can be called.
// Note: new functions are implemented in classes such as ArtificialTsunamiScenario (as a derived class of Scenario)
Scenarios::Scenario *getScenarioBasedOnName(std::string &name) {
    if (reinterpret_cast<std::string & >(name) == "RadialDamBreakScenario") {
        auto *scenario = new Scenarios::RadialDamBreakScenario;
        return scenario;
    } else if (reinterpret_cast<std::string & >(name) == "BathymetryDamBreakScenario") {
        auto *scenario = new Scenarios::BathymetryDamBreakScenario;
        return scenario;
    } else {
        auto *scenario = new Scenarios::ArtificialTsunamiScenario;
        return scenario;
    }
}


// Source: https://stackoverflow.com/questions/41820039/jstringjni-to-stdstringc-with-utf8-characters @Slerte
std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes,
                                                                       env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *) pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}


