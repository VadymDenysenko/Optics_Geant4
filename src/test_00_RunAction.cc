/// \file test_00_RunAction.cc
/// \brief Implementation of the test_00_RunAction class
//
//
#include "test_00_RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"

#include "test_00_DetectorConstruction.hh"
#include "test_00_SteppingAction.hh"

#include <ctime>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_RunAction::test_00_RunAction()
  : fSaveRndm(0), fAutoSeed(false)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_RunAction::~test_00_RunAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  G4RunManager::GetRunManager()->SetRandomNumberStoreDir("random/");

  if(fAutoSeed)
  {
     // automatic (time-based) random seeds for each run
     G4cout << "*******************" << G4endl;
     G4cout << "*** AUTOSEED ON ***" << G4endl;
     G4cout << "*******************" << G4endl;
     long seeds[2];
     time_t systime = time(NULL);
     seeds[0] = (long) systime;
     seeds[1] = (long) (systime*G4UniformRand());
     G4Random::setTheSeeds(seeds);
     G4Random::showEngineStatus();
  }else
  {
     G4Random::showEngineStatus();
  }

  if(fSaveRndm > 0)
    G4Random::saveEngineStatus("BeginOfRun.rndm");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_RunAction::EndOfRunAction(const G4Run* )
{
  if(fSaveRndm == 1)
  {
     G4Random::showEngineStatus();
     G4Random::saveEngineStatus("endOfRun.rndm");
  }
}
