/// \file test_00_ActionInitialization.cc
/// \brief Implementation of the test_00_ActionInitialization class
//
//
#include "test_00_ActionInitialization.hh"
#include "test_00_RunAction.hh"
#include "test_00_SteppingAction.hh"
#include "test_00_PrimaryGeneratorAction.hh"
#include "test_00_DetectorConstruction.hh"

#include "G4GeneralParticleSource.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_ActionInitialization::test_00_ActionInitialization(test_00_DetectorConstruction* det)
 : G4VUserActionInitialization(), fDetector(det)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_ActionInitialization::~test_00_ActionInitialization()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_ActionInitialization::BuildForMaster() const
{
  SetUserAction(new test_00_RunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_ActionInitialization::Build() const
{
  SetUserAction(new test_00_PrimaryGeneratorAction());

  test_00_RunAction* runAction = new test_00_RunAction();

  SetUserAction(runAction);
  SetUserAction(new test_00_SteppingAction(fDetector));
}
