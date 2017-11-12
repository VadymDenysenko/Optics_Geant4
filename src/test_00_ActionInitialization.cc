/// \file test_00_ActionInitialization.cc
/// \brief Implementation of the test_00_ActionInitialization class
//
//
#include "test_00_ActionInitialization.hh"

#include "test_00_PrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_ActionInitialization::test_00_ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_ActionInitialization::~test_00_ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_ActionInitialization::BuildForMaster() const
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_ActionInitialization::Build() const
{
  SetUserAction(new test_00_PrimaryGeneratorAction());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

