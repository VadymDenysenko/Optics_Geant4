/// \file test_00_OpticalPhysics.cc
/// \brief Implementation of the test_00_OpticalPhysics class
//
//
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

#include "test_00_OpticalPhysics.hh"

test_00_OpticalPhysics::test_00_OpticalPhysics(G4bool toggle)
    : G4VPhysicsConstructor("Optical")
{
  ftest_00_Process           = NULL;
  fScintProcess              = NULL;
  fCerenkovProcess           = NULL;
  fBoundaryProcess           = NULL;
  fAbsorptionProcess         = NULL;
  fRayleighScattering        = NULL;
  fMieHGScatteringProcess    = NULL;

  fAbsorptionOn              = toggle;
}

test_00_OpticalPhysics::~test_00_OpticalPhysics() { }

#include "G4OpticalPhoton.hh"

void test_00_OpticalPhysics::ConstructParticle()
{
  G4OpticalPhoton::OpticalPhotonDefinition();
}

#include "G4ProcessManager.hh"

void test_00_OpticalPhysics::ConstructProcess()
{
    G4cout << "test_00_OpticalPhysics:: Add Optical Physics Processes"
           << G4endl;

  ftest_00_Process = new G4OpWLS();

  fScintProcess = new G4Scintillation();
  fScintProcess->SetScintillationYieldFactor(1.0);
  fScintProcess->SetTrackSecondariesFirst(true);

  fCerenkovProcess = new G4Cerenkov();
  fCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  fCerenkovProcess->SetTrackSecondariesFirst(true);

  fAbsorptionProcess      = new G4OpAbsorption();
  fRayleighScattering     = new G4OpRayleigh();
  fMieHGScatteringProcess = new G4OpMieHG();
  fBoundaryProcess        = new G4OpBoundaryProcess();

  G4ProcessManager* pManager =
                G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

  if (fAbsorptionOn) 
    pManager->AddDiscreteProcess(fAbsorptionProcess);
  
  pManager->AddDiscreteProcess(fBoundaryProcess);

  ftest_00_Process->UseTimeProfile("exponential");

  pManager->AddDiscreteProcess(ftest_00_Process);

  fScintProcess->SetScintillationYieldFactor(1.);
  fScintProcess->SetScintillationExcitationRatio(0.0);
  fScintProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  fScintProcess->AddSaturation(emSaturation);

  aParticleIterator->reset();
  while ( (*aParticleIterator)() ){

    G4ParticleDefinition* particle = aParticleIterator->value();
    G4String particleName = particle->GetParticleName();

    pManager = particle->GetProcessManager();
    if (!pManager) {
       std::ostringstream o;
       o << "Particle " << particleName << "without a Process Manager";
       G4Exception("test_00_OpticalPhysics::ConstructProcess()","",
                    FatalException,o.str().c_str());
    }

    if(fScintProcess->IsApplicable(*particle)){
      pManager->AddProcess(fScintProcess);
      pManager->SetProcessOrderingToLast(fScintProcess,idxAtRest);
      pManager->SetProcessOrderingToLast(fScintProcess,idxPostStep);
    }

  }
}

void test_00_OpticalPhysics::SetNbOfPhotonsCerenkov(G4int maxNumber)
{
  fCerenkovProcess->SetMaxNumPhotonsPerStep(maxNumber);
}
