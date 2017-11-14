/// \file test_00_SteppingAction.cc
/// \brief Implementation of the test_00_SteppingAction class
//
//
#include "G4Run.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4VPhysicalVolume.hh"

#include "test_00_SteppingAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include <sstream>

// Purpose: Save relevant information into User Track Information

G4int test_00_SteppingAction::fMaxRndmSave = 10000;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_SteppingAction::test_00_SteppingAction(test_00_DetectorConstruction*
                                               detector)
  : fDetector(detector)
{
  fCounter = 0;
  fAbsorbed = 0;
  testCounter = 0;
  saveFile.open("other.txt");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_SteppingAction::~test_00_SteppingAction()
{
  G4cout << "Your counts here: " << fCounter
         << " || Absorbed: " << fAbsorbed << G4endl;
  saveFile.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int test_00_SteppingAction::GetCounts()
{
  return fCounter;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void test_00_SteppingAction::saveRandomStatus(G4String subDir)
// save the random status into a sub-directory
// Pre: subDir must be empty or ended with "/"
{
  // don't save if the maximum amount has been reached
  if(test_00_SteppingAction::fMaxRndmSave == 0)
    return;

  G4RunManager* theRunManager = G4RunManager::GetRunManager();
  G4String randomNumberStatusDir = theRunManager->GetRandomNumberStoreDir();

  G4String fileIn  = randomNumberStatusDir + "currentEvent.rndm";

  std::ostringstream os;

  os << "run" << theRunManager->GetCurrentRun()->GetRunID() << "evt"
     << theRunManager->GetCurrentEvent()->GetEventID() << ".rndm" << '\0';

  G4String fileOut = randomNumberStatusDir + subDir + os.str();

  G4String copCmd = "/control/shell cp "+fileIn+" "+fileOut;
  G4UImanager::GetUIpointer()->ApplyCommand(copCmd);

  test_00_SteppingAction::fMaxRndmSave--;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_SteppingAction::UserSteppingAction(const G4Step* theStep)
{
  G4Track* theTrack = theStep->GetTrack();
  if(theTrack->GetCurrentStepNumber() == 1)
  {
    //const G4int id = testCounter;
    //G4cout << theStep->GetTrack()->GetTrackID() << " : ";
    theStep->GetTrack()->SetTrackID(++testCounter);
    //G4cout << theStep->GetTrack()->GetTrackID() << "; ";
  }

  G4StepPoint* thePrePoint  = theStep->GetPreStepPoint();
  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();

  G4double postX = thePostPoint->GetPosition().x();
  G4double postY = thePostPoint->GetPosition().y();
  G4double postZ = thePostPoint->GetPosition().z();

  G4double preX = thePrePoint->GetPosition().x();
  G4double preY = thePrePoint->GetPosition().y();
  G4double preZ = thePrePoint->GetPosition().z();

  G4VPhysicalVolume* thePrePV  = thePrePoint->GetPhysicalVolume();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  G4String thePrePVname  = " ";
  G4String thePostPVname = " ";

  if(thePostPV)
  {
     thePrePVname  = thePrePV->GetName();
     thePostPVname = thePostPV->GetName();
     //G4cout << "Pre: " << thePrePVname
     //        << " Post: " << thePostPVname
     //        << "; " << x << ":" << y << ":" << z << G4endl;
  }
  G4int id = theStep->GetTrack()->GetTrackID();
  SaveParticles(preX, preY, preZ, thePrePVname,
                postX, postY, postZ, thePostPVname,
                id);

  if(thePostPVname == "Counter")
  {
    fCounter++;
    theTrack->SetTrackStatus(fStopAndKill);
    SaveParticles(id, postX, postY, postZ);
  }
  if(thePrePVname == "Volume" && thePostPVname == "Volume")
    fAbsorbed++;

}
