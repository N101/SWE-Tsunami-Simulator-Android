#include <jni.h>
#include <string>

std::string runner_main();

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_testcpp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_testcpp_MainActivity_main(JNIEnv *env, jobject thiz) {
    // TODO: implement main()
    return env->NewStringUTF(runner_main().c_str());
}

#include <iostream>

#include "Source//Blocks/DimensionalSplitting.hpp"
//#include "../Blocks/WavePropagationBlock.hpp"
#include "Source/Scenarios/RadialDamBreakScenario.hpp"
#include "Source/Scenarios/TsunamiScenario.hpp"
#include "Source/Scenarios/ArtificialTsunamiScenario.hpp"
//#include "Blocks/Block.hpp"
#include "Source/Tools/Args.hpp"
//#include "Source/Tools/Logger.hpp"
//#include "Source/Writers/Writer.hpp"
#include "Source/BoundaryEdge.hpp"


/**
 * @note:
 * an early experimental version, only switched scenario to TsunamiScenario
 * compiled and run (?) withouit error, but many bugs expected
 * */
//int main(int argc, char** argv) {
std::string runner_main() {
//  Tools::Args args;
//  args.addOption("grid-size-x", 'x', "Number of cells in x direction");
//  args.addOption("grid-size-y", 'y', "Number of cells in y direction");
//  args.addOption("output-basepath", 'o', "Output base file name");
//  args.addOption("number-of-checkpoints", 'n', "Number of checkpoints to write output files");
//  args.addOption("Boundary condition", 'a', "Boundary condition");  //! command line argument for setting the boundary condition types
//  args.addOption("Simulation time", 't', "Simulation time");
//
//  Tools::Args::Result ret = args.parse(argc, argv, true);
//
//  switch (ret) {
//  case Tools::Args::Result::Error:
//    return EXIT_FAILURE;
//  case Tools::Args::Result::Help:
//    return EXIT_SUCCESS;
//  default:
//    break;
//  }

  // Tools::Logger::logger.printWelcomeMessage();

  // parse arguments
//  int         numberOfGridCellsX  = args.getArgument<int>("grid-size-x", 1000);
//  int         numberOfGridCellsY  = args.getArgument<int>("grid-size-y", 1000);
//  std::string baseName            = args.getArgument<std::string>("output-basepath", "SWE");
//  int         numberOfCheckPoints = args.getArgument<int>(
//    "number-of-checkpoints", 20
//  ); //! Number of checkpoints for visualization (at each checkpoint in time, an output file is written).


//==================================================================

  std::stringstream output;

  int         numberOfGridCellsX  = 50;
  int         numberOfGridCellsY  = 50;
  std::string baseName            = "SWE";
  int         numberOfCheckPoints = 1;


  //std::string boundaryCond        = args.getArgument<std::string>("Boundary condition", "PPPP");
  std::string boundaryCond        = "PPPP";

  //Scenarios::TsunamiScenario scenario;
  Scenarios::RadialDamBreakScenario scenario;

  RealType cellSize_x = (scenario.getBoundaryPos(BoundaryEdge::Right) - scenario.getBoundaryPos(BoundaryEdge::Left))
                        / numberOfGridCellsX;
  RealType cellSize_y = (scenario.getBoundaryPos(BoundaryEdge::Top) - scenario.getBoundaryPos(BoundaryEdge::Bottom))
                        / numberOfGridCellsY;

  auto wave_block = Blocks::Block::getBlockInstance(numberOfGridCellsX, numberOfGridCellsY, cellSize_x, cellSize_y);
  wave_block->initialiseScenario(0, 0, scenario, false);
  // Get the final simulation time from the scenario
  double endSimulationTime = scenario.getEndSimulationTime();

  double* checkPoints = new double[numberOfCheckPoints + 1];

  // Compute the checkpoints in time
  for (int cp = 0; cp <= numberOfCheckPoints; cp++) {
    checkPoints[cp] = cp * (endSimulationTime / numberOfCheckPoints);
  }

  // Boundary size of the ghost layers
//  Writers::BoundarySize boundarySize = {{1, 1, 1, 1}};
//
//  std::string fileName = Writers::generateBaseFileName(baseName, 0, 0);
//  auto        writer   = Writers::Writer::createWriterInstance(
//    fileName, wave_block->getBathymetry(), boundarySize, numberOfGridCellsX, numberOfGridCellsY, cellSize_x, cellSize_y, 0 * 16, 0 * 16, 0, 0, 0
//  );

  //! Set boundaryTypes in Block::boundary_
  for (int i=0; i < 4; i++) {
      BoundaryType curr;
      //std::cout << "boundaryCond = " << boundaryCond << std::endl;
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
      boundaryCond = boundaryCond.substr(1);
  }

  //Tools::Logger::logger.printOutputTime(0.0);

  // Write zero time step
  //writer->writeTimeStep(wave_block->getWaterHeight(), wave_block->getDischargeHu(), wave_block->getDischargeHv(), 0.0, nullptr);

  unsigned int iterations     = 0;
  double       simulationTime = 0.0;
  //Tools::Logger::logger.printStartMessage();
  //Tools::Logger::logger.initWallClockTime(time(NULL));
  // Loop over checkpoints
  for (int cp = 0; cp <= numberOfCheckPoints; cp++) {
    // Do time steps until next checkpoint is reached
    while (simulationTime < checkPoints[cp]) {
      // Tools::Logger::logger.resetClockToCurrentTime("CPU-Communication");
      //Tools::Logger::logger.resetClockToCurrentTime("CPU");
      output << "running simulation at time " << simulationTime << std::endl;
      // Set values in ghost cells
      wave_block->setGhostLayer();

      // Compute numerical flux on each edge
      wave_block->computeNumericalFluxes();

      RealType maxTimeStepWidth = wave_block->getMaxTimeStep();

      // Update the cell values
      wave_block->updateUnknowns(maxTimeStepWidth);

      //Tools::Logger::logger.updateTime("CPU");
      // Tools::Logger::logger.updateTime("CPU-Communication");

      // Update simulation time with time step width
      simulationTime += maxTimeStepWidth;
      iterations++;
    }

//    std::cout << "\n\nnew checkpoint\n";
    //std::cout << "new checkpoint after " << iterations << " iterations\n";
    // Write output
//    writer->writeTimeStep(
//      wave_block->getWaterHeight(), wave_block->getDischargeHu(), wave_block->getDischargeHv(), simulationTime,
//      wave_block->getBoundaryType()
//    );
  }

//  Tools::Logger::logger.printStatisticsMessage();
//  Tools::Logger::logger.printTime("CPU", "CPU Time");
//  // Tools::Logger::logger.printTime("CPU-Communicaion", "CPU + Communication time");
//  Tools::Logger::logger.printWallClockTime(time(NULL));
//  Tools::Logger::logger.printIterationsDone(iterations);
//
//  Tools::Logger::logger.printFinishMessage();

  delete wave_block;
  delete[] checkPoints;
  std::string ret = output.str();
  return ret;
  //return std::string("hello");

  //===============================================================================

}


