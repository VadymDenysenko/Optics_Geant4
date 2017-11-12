/// \file test_00_DetectorConstruction.hh
/// \brief Implementation of the test_00_DetectorConstruction class
//
//
#ifndef test_00_DetectorConstruction_h
#define test_00_DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class test_00_DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    test_00_DetectorConstruction();
    virtual ~test_00_DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

  private:
    G4GDMLParser fParser;
    G4String fReadFile;
    G4VSolid* GDML;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
