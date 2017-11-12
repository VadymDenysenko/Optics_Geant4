/// \file test_00_DetectorConstruction.cc
/// \brief Implementation of the test_00_DetectorConstruction class
//
//
#include "test_00_Materials.hh"
#include "test_00_SensitiveDetector.hh"
#include "test_00_DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4GDMLParser.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_DetectorConstruction::test_00_DetectorConstruction():fMaterials(NULL)
{
    fReadFile = "light-guideMiddleNew2.gdml";
    fParser.Read(fReadFile);
    GDML = fParser.GetWorldVolume()->GetLogicalVolume()->GetDaughter(0)->
                                                 GetLogicalVolume()->GetSolid();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_DetectorConstruction::~test_00_DetectorConstruction()
{
    if(fMaterials)
      delete fMaterials;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* test_00_DetectorConstruction::Construct()
{
    // ------------- Materials -------------
    fMaterials = test_00_Materials::GetInstance();
    //
    // ------------- Volumes --------------
    /*World*/
    G4VSolid* wBox = new G4Box("box", 1.*m, 1.*m, 1.*m);
    G4LogicalVolume* lWorld = new G4LogicalVolume(wBox,
                                          FindMaterial("G4_Galactic"), "World");
    G4VPhysicalVolume* pWorld = new G4PVPlacement(0,G4ThreeVector(),
                                                  lWorld, "World", 0, false, 0);
    /*end World
      Ring*/
    G4VSolid* rTubs = new G4Tubs("tubs", 26.*mm, 30.*mm, 1.*mm,
                                                              0.*deg, 360.*deg);
    G4LogicalVolume* lRing = new G4LogicalVolume(rTubs,
                                                FindMaterial("G4_AIR"), "Ring");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 33.25*mm + 0.5*mm), lRing,
                                                      "Ring", lWorld, false, 0);
    /*end Ring
      Counter*/
    G4VSolid* cTubs = new G4Tubs("tubs", 0.*mm, 15.*mm, 1.5*mm,
                                                              0.*deg, 360.*deg);
    G4LogicalVolume* lCounter = new G4LogicalVolume(cTubs,
                                              FindMaterial("G4_Al"), "Counter");
    new G4PVPlacement(0, G4ThreeVector(0., 0., -1.5*mm), lCounter, "Counter",
                                                              lWorld, false, 0);
    /*end Counter
      GDMLVolume*/
    G4LogicalVolume* lVolume = new G4LogicalVolume(GDML,
//                                               FindMaterial("G4_Al"), "Volume");
                                          FindMaterial("PMMA"), "Volume");
    new G4PVPlacement(0, G4ThreeVector(), lVolume, "Volume", lWorld, false, 0);

    return pWorld;
}

void test_00_DetectorConstruction::ConstructSDandField()
{
    static G4ThreadLocal G4bool fInit = false;
    if(!fInit)
    {
        fInit = false;
    }
}

G4Material* test_00_DetectorConstruction::FindMaterial(G4String name)
{
    G4Material* material = G4Material::GetMaterial(name, true);
    return material;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
