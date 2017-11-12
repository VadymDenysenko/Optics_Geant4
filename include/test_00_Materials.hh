/// \file test_00_Materials.hh
/// \brief Definition of the test_00_Materials class
//
//
#ifndef test_00_Materials_h
#define test_00_Materials_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

class test_00_Materials
{
  public:

    virtual ~test_00_Materials();
 
    static test_00_Materials* GetInstance();

    G4Material* GetMaterial(const G4String);
 
  private:
 
    test_00_Materials();

    void CreateMaterials();

  private:

    static test_00_Materials* fInstance;

    G4NistManager*     fNistMan;

    G4Material*        fAir;

    G4Material*        fPMMA;
    G4Material*        fPethylene;
    G4Material*        fFPethylene;
    G4Material*        fPolystyrene;
    G4Material*        fSilicone;
    G4Material*        fCoating;

};

#endif
