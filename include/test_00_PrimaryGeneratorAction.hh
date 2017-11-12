/// \file test_00_PrimaryGeneratorAction.hh
/// \brief Implementation of the test_00_PrimaryGeneratorAction class
//
//
#ifndef test_00_PrimaryGeneratorAction_h
#define test_00_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class test_00_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
	test_00_PrimaryGeneratorAction();
    virtual ~test_00_PrimaryGeneratorAction();

    // static access method
    static const test_00_PrimaryGeneratorAction* Instance();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);
  public:

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);
    // method to access particle gun
    const G4GeneralParticleSource* GetParticleGun(){ return pgun; }

  private:
    static test_00_PrimaryGeneratorAction* fgInstance;
    G4GeneralParticleSource* pgun;

};
#endif
