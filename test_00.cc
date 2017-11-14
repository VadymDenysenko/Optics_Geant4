#include "G4RunManager.hh"

#include "G4UImanager.hh"

#include "test_00_PhysicsList.hh"
#include "test_00_DetectorConstruction.hh"

#include "test_00_ActionInitialization.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " test_00 [-m macro ] [-u UIsession] [-r seed] "
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  if ( argc > 9 )
  {
    PrintUsage();
    return 1;
  }

  G4String macro;
  G4String session;

  G4long myseed = 345354;
  for(G4int i=1; i<argc; i=i+2 )
  {
    if(G4String(argv[i]) == "-m")
      macro = argv[i+1];
    else
    if(G4String(argv[i]) == "-u")
      session = argv[i+1];
    else
    if(G4String(argv[i]) == "-r")
      myseed = atoi(argv[i+1]);
    else
    {
      PrintUsage();
      return 1;
    }
  }

  // Choose the Random engine
  //
  //CLHEP::RanecuEngine * engine= new CLHEP::RanecuEngine();
  //engine->setSeed(1000,0);
  //G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4Random::setTheEngine(new CLHEP::RanecuEngine());

  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // Seed the random number generator manually
  G4Random::setTheSeed(myseed);
  G4String physName = "QGSP_BERT_HP";

  // Set mandatory initialization classes
  //
  // Detector construction
  test_00_DetectorConstruction* detector = new test_00_DetectorConstruction();
  runManager->SetUserInitialization(detector);
  // Physics list
  runManager->SetUserInitialization(new test_00_PhysicsList(physName));
  // User action initialization
  runManager->SetUserInitialization(new test_00_ActionInitialization(detector));

  // Initialize G4 kernel
  //
  runManager->Initialize();

#ifdef G4VIS_USE
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if(macro.size())
  {
     // Batch mode
     G4String command = "/control/execute ";
     UImanager->ApplyCommand(command+macro);
  }
  else // Define UI session for interactive mode
  {
#ifdef G4UI_USE
     G4UIExecutive * ui = new G4UIExecutive(argc,argv,session);
#ifdef G4VIS_USE
     UImanager->ApplyCommand("/control/execute vis.mac");
#endif
     if(ui->IsGUI())
        UImanager->ApplyCommand("/control/execute gui.mac");
     ui->SessionStart();
     delete ui;
#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
