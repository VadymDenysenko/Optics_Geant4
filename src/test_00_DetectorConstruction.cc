/// \file test_00_DetectorConstruction.cc
/// \brief Implementation of the test_00_DetectorConstruction class
//
//
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

test_00_DetectorConstruction::test_00_DetectorConstruction()
{
    fReadFile = "light-guideMiddleNew2.gdml";
    fParser.Read(fReadFile);
    GDML = fParser.GetWorldVolume()->GetLogicalVolume()->GetDaughter(0)->
                                                 GetLogicalVolume()->GetSolid();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

test_00_DetectorConstruction::~test_00_DetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* test_00_DetectorConstruction::Construct()
{
    // ------------- Materials -------------
    G4NistManager* fNist = G4NistManager::Instance();

    G4double density;
    std::vector<G4int> natoms;
    std::vector<G4String> elements;
    /*PETHYLENE*/
    elements.push_back("C");    natoms.push_back(2);
    elements.push_back("H");    natoms.push_back(4);
    density = 1.200*g/cm3;

    G4Material* mPETHYLENE = fNist->ConstructNewMaterial("Pethylene", elements,
                                                               natoms, density);
    elements.clear();
    natoms.clear();
    /*end PETHYLENE
      AIR*/
    G4Material* mAIR = fNist->FindOrBuildMaterial("G4_AIR");
    /*end AIR*/
    //
    //-------- Material properties ---------
    G4double photonEnergy[] = {4.*eV};
    const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);
    /*PETHYLENE*/
    G4double refractiveIndexPETHYLENE[] = {1.49};
    assert(sizeof(refractiveIndexPETHYLENE) == sizeof(photonEnergy));
    G4double absLengthPETHYLENE[] = {20.*m};
    assert(sizeof(absLengthPETHYLENE) == sizeof(photonEnergy));

    G4MaterialPropertiesTable* mptPETHYLENE = new G4MaterialPropertiesTable();
    mptPETHYLENE->AddProperty("RINDEX", photonEnergy, refractiveIndexPETHYLENE,
                                                                      nEntries);
    mptPETHYLENE->AddProperty("ABSLENGTH", photonEnergy, absLengthPETHYLENE,
                                                                      nEntries);

    mPETHYLENE->SetMaterialPropertiesTable(mptPETHYLENE);
    /*end PETHYLENE
      AIR*/
    G4double refractiveIndexAIR[] = {1.};
    assert(sizeof(refractiveIndexAIR) == sizeof(photonEnergy));

    G4MaterialPropertiesTable* mptAIR = new G4MaterialPropertiesTable();
    mptAIR->AddProperty("RINDEX", photonEnergy, refractiveIndexAIR, nEntries);

    mAIR->SetMaterialPropertiesTable(mptAIR);
    /*end AIR*/
    //
    // ------------- Volumes --------------
    /*World*/
    G4VSolid* wBox = new G4Box("box", 1.*m, 1.*m, 1.*m);
    G4LogicalVolume* lWorld = new G4LogicalVolume(wBox, mAIR, "World");
    G4VPhysicalVolume* pWorld = new G4PVPlacement(0,G4ThreeVector(),
                                                  lWorld, "World", 0, false, 0);
    /*end World
      Ring*/
    G4VSolid* rTubs = new G4Tubs("tubs", 26.*mm, 30.*mm, 1.*mm,
                                                              0.*deg, 360.*deg);
    G4LogicalVolume* lRing = new G4LogicalVolume(rTubs, mPETHYLENE, "Ring");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 33.25*mm + 0.5*mm), lRing,
                                                      "Ring", lWorld, false, 0);
    /*end Ring
      Counter*/
    G4VSolid* cTubs = new G4Tubs("tubs", 0.*mm, 15.*mm, 1.5*mm,
                                                              0.*deg, 360.*deg);
    G4LogicalVolume* lCounter = new G4LogicalVolume(cTubs, mPETHYLENE,
                                                                     "Counter");
    new G4PVPlacement(0, G4ThreeVector(0., 0., -1.5*mm), lCounter, "Counter",
                                                              lWorld, false, 0);
    /*end Counter
      GDMLVolume*/
    G4LogicalVolume* lVolume = new G4LogicalVolume(GDML, mPETHYLENE, "Volume");
    new G4PVPlacement(0, G4ThreeVector(), lVolume, "Volume", lWorld, false, 0);
    /*end GDMLVolume*/








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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
