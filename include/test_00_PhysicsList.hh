/// \file test_00_PhysicsList.hh
/// \brief Implementation of the test_00_PhysicsList class
//
//
#ifndef test_00_PhysicsList_h
#define test_00_PhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;
class test_00_PhysicsListMessenger;

class test_00_StepMax;
class test_00_OpticalPhysics;

class test_00_PhysicsList: public G4VModularPhysicsList
{
  public:

    test_00_PhysicsList(G4String);
    virtual ~test_00_PhysicsList();

    void SetCuts();
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);

    void SetStepMax(G4double);
    test_00_StepMax* GetStepMaxProcess();
    void AddStepMax();

    /// Remove specific physics from physics list.
    void RemoveFromPhysicsList(const G4String&);

    /// Make sure that the physics list is empty.
    void ClearPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

    // Turn on or off the absorption process
    void SetAbsorption(G4bool);

    void SetNbOfPhotonsCerenkov(G4int);

    void SetVerbose(G4int);

private:

    G4double fCutForGamma;
    G4double fCutForElectron;
    G4double fCutForPositron;

    test_00_StepMax* fStepMaxProcess;

    test_00_OpticalPhysics* fOpticalPhysics;

    G4bool fAbsorptionOn;
    
    G4VMPLData::G4PhysConstVectorData* fPhysicsVector;

};

#endif
