/// \file test_00_PrimaryGeneratorAction.cc
/// \brief Implementation of the test_00_PrimaryGeneratorAction class
//
//
#include "test_00_PrimaryGeneratorAction.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
test_00_PrimaryGeneratorAction* test_00_PrimaryGeneratorAction::fgInstance = 0;
const test_00_PrimaryGeneratorAction* test_00_PrimaryGeneratorAction::Instance()
{
// Static acces function via G4RunManager

  return fgInstance;
}
test_00_PrimaryGeneratorAction::test_00_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
  pgun = new G4GeneralParticleSource();
  fgInstance = this;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("opticalphoton");

  pgun->SetParticleDefinition(particle);
  pgun->SetParticleTime(0.0*ns);

}
test_00_PrimaryGeneratorAction::~test_00_PrimaryGeneratorAction()
{
  delete pgun;
  fgInstance = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	pgun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_PrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void test_00_PrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (pgun->GetParticleDefinition()->GetParticleName()!="opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = pgun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 pgun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
