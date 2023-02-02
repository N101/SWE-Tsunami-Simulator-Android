//#include <iostream>
//
//#include "../Blocks/DimensionalSplitting.hpp"
////#include "../Blocks/WavePropagationBlock_1D.hpp"
//#include "../Scenarios/RadialDamBreakScenario.hpp"
//#include "../Scenarios/TsunamiScenario.hpp"
//#include "../Scenarios/ArtificialTsunamiScenario.hpp"
////#include "Blocks/Block.hpp"
//#include "../Tools/Args.hpp"
//#include "../Tools/Logger.hpp"
////#include "Writers/Writer.hpp"
//
///**
// * @note:
// * an early experimental version, only switched scenario to TsunamiScenario
// * compiled and run (?) withouit error, but many bugs expected
// * */
//int main(int argc, char** argv) {
//
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
//
//  // Tools::Logger::logger.printWelcomeMessage();
//
//  // parse arguments
//  int         numberOfGridCellsX  = args.getArgument<int>("grid-size-x", 1000);
//  int         numberOfGridCellsY  = args.getArgument<int>("grid-size-y", 1000);
//  std::string baseName            = args.getArgument<std::string>("output-basepath", "SWE");
//  int         numberOfCheckPoints = args.getArgument<int>(
//    "number-of-checkpoints", 20
//  ); //! Number of checkpoints for visualization (at each checkpoint in time, an output file is written).
//  std::string boundaryCond        = args.getArgument<std::string>("Boundary condition", "PPPP");
//
//  Scenarios::TsunamiScenario scenario;
//
//  RealType cellSize_x = (scenario.getBoundaryPos(BoundaryEdge::Right) - scenario.getBoundaryPos(BoundaryEdge::Left))
//                        / numberOfGridCellsX;
//  RealType cellSize_y = (scenario.getBoundaryPos(BoundaryEdge::Top) - scenario.getBoundaryPos(BoundaryEdge::Bottom))
//                        / numberOfGridCellsY;
//
//  auto wave_block = Blocks::Block::getBlockInstance(numberOfGridCellsX, numberOfGridCellsY, cellSize_x, cellSize_y);
//  wave_block->initialiseScenario(0, 0, scenario, false);
//  // Get the final simulation time from the scenario
//  double endSimulationTime = scenario.getEndSimulationTime();
//
//  double* checkPoints = new double[numberOfCheckPoints + 1];
//
//  // Compute the checkpoints in time
//  for (int cp = 0; cp <= numberOfCheckPoints; cp++) {
//    checkPoints[cp] = cp * (endSimulationTime / numberOfCheckPoints);
//  }
//
//  // Boundary size of the ghost layers
//  Writers::BoundarySize boundarySize = {{1, 1, 1, 1}};
//
//  std::string fileName = Writers::generateBaseFileName(baseName, 0, 0);
//  auto        writer   = Writers::Writer::createWriterInstance(
//    fileName, wave_block->getBathymetry(), boundarySize, numberOfGridCellsX, numberOfGridCellsY, cellSize_x, cellSize_y, 0 * 16, 0 * 16, 0, 0, 0
//  );
//
//  //! Set boundaryTypes in Block::boundary_
//  for (int i=0; i < 4; i++) {
//      BoundaryType curr;
//      std::cout << "boundaryCond = " << boundaryCond << std::endl;
//      if (boundaryCond.at(0) == 'W') {
//      // if((boundaryCond.front()).compare('W')) {
//          curr = Wall;
//      } else if (boundaryCond.at(0) == 'O') {
//          curr = Outflow;
//      } else {
//          // default/wrong parameters ==> change to default _Passive_ (block constructor also initializes as passive)
//          curr = Passive;
//      }
//      wave_block->setBoundaryType(BoundaryEdge(i), curr);
//      boundaryCond = boundaryCond.substr(1);
//  }
//
//  Tools::Logger::logger.printOutputTime(0.0);
//
//  // Write zero time step
//  writer->writeTimeStep(wave_block->getWaterHeight(), wave_block->getDischargeHu(), wave_block->getDischargeHv(), 0.0, nullptr);
//
//  unsigned int iterations     = 0;
//  double       simulationTime = 0.0;
//  Tools::Logger::logger.printStartMessage();
//  Tools::Logger::logger.initWallClockTime(time(NULL));
//  // Loop over checkpoints
//  for (int cp = 1; cp <= numberOfCheckPoints; cp++) {
//    // Do time steps until next checkpoint is reached
//    while (simulationTime < checkPoints[cp]) {
//      // Tools::Logger::logger.resetClockToCurrentTime("CPU-Communication");
//      Tools::Logger::logger.resetClockToCurrentTime("CPU");
//      //std::cout << "running simulation at time " << simulationTime << std::endl;
//      // Set values in ghost cells
//      wave_block->setGhostLayer();
//
//      // Compute numerical flux on each edge
//      wave_block->computeNumericalFluxes();
//
//      RealType maxTimeStepWidth = wave_block->getMaxTimeStep();
//
//      // Update the cell values
//      wave_block->updateUnknowns(maxTimeStepWidth);
//
//      Tools::Logger::logger.updateTime("CPU");
//      // Tools::Logger::logger.updateTime("CPU-Communication");
//
//      // Update simulation time with time step width
//      simulationTime += maxTimeStepWidth;
//      iterations++;
//    }
//
////    std::cout << "\n\nnew checkpoint\n";
//    std::cout << "new checkpoint after " << iterations << " iterations\n";
//    // Write output
//    writer->writeTimeStep(
//      wave_block->getWaterHeight(), wave_block->getDischargeHu(), wave_block->getDischargeHv(), simulationTime,
//      wave_block->getBoundaryType()
//    );
//  }
//
//  Tools::Logger::logger.printStatisticsMessage();
//  Tools::Logger::logger.printTime("CPU", "CPU Time");
//  // Tools::Logger::logger.printTime("CPU-Communicaion", "CPU + Communication time");
//  Tools::Logger::logger.printWallClockTime(time(NULL));
//  Tools::Logger::logger.printIterationsDone(iterations);
//
//  Tools::Logger::logger.printFinishMessage();
//
//  delete wave_block;
//  delete[] checkPoints;
//}







/*
// #define FILE_PATH_BATH "/work/files/tohoku_2011/tohoku_gebco_ucsb3_2000m_hawaii_bath.nc"
// #define FILE_PATH_DISPL "/work/files/tohoku_gebco_ucsb3_2000m_hawaii_displ.nc"
// #include <iostream>
// #ifdef ENABLE_NETCDF
// //#include <netcdf>
// #include <netcdfcpp.h>
// //#include <netcdf.h>

// // using namespace netCDF;
// // using namespace netCDF::exceptions;

// // clarification:
// // only libnetcdf.so and libnetcdf_c++.so get linked entsprechen netcdf.h and netcdfcpp.h(make VERBOSE=1)
// // but namespace netCDF is in libnetcdf_c++4.so, don't know how to link it
// // netcdfcpp.h is not included in <netcdf>
// // <netcdf> is a collection of ncFile.h ...

// int main() {
//   NcFile file(FILE_PATH_BATH, NcFile::ReadOnly, NULL, 0, NcFile::Classic);
//   int    num_dims = file.num_dims();
//   int    num_vars = file.num_vars();
//   int    num_atts = file.num_atts();
//   std::cout << "dims: " << num_dims << std::endl;
//   std::cout << "vars: " << num_vars << std::endl;
//   std::cout << "atts: " << num_atts << std::endl;

//   NcDim*  dim_1      = file.get_dim(1);
//   NcVar*  var_2      = file.get_var(2);
//   NcToken name_dim_1 = dim_1->name();
//   NcToken name_var_2 = var_2->name();
//   std::cout << "name_dim_1: " << name_dim_1 << std::endl;
//   std::cout << "name_var_2: " << name_var_2 << std::endl;

//   NcValues* values = var_2->values();
//   int       val    = values->as_int(1);
//   std::cout << "1.val: " << val << std::endl;

//   // int ncid1, ncid2, varxid, varyid, varzid, grpxid, grpyid, grpzid;
//   // int  x, y, status1, status2;
//   // double reader[3500][2000];

//   // status1 = nc_open(FILE_NAME_BATH, NC_NOWRITE, &ncid1);
//   // std::cout <<  "stats1_open: " << status1 << std::endl;

//   // status1 = nc_inq_varid(ncid, "x", &varid);
//   // std::cout <<  "stats1_inq: " << status1 << std::endl;
// }

// #endif*/
