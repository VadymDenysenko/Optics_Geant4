/// \file test_00_SensitiveDetector.cc
/// \brief Definition of the test_00_SensitiveDetector class
//
//
#include "test_00_SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include <fstream>

test_00_SensitiveDetector::test_00_SensitiveDetector(G4String name):
G4VSensitiveDetector(name){}

G4bool test_00_SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory*)
{
      G4cout << "Hello!" << G4endl;
    counter ++;

    step->GetTrack()->SetTrackStatus(fStopAndKill);
    return true;
}

test_00_SensitiveDetector::~test_00_SensitiveDetector(){

  G4cout << "HERE YOUR NUMBER!: " << counter << G4endl;

}
