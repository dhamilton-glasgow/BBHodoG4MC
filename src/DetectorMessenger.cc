#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

//---------------------------------------------------------------------------

DetectorMessenger::DetectorMessenger(DetectorConstruction* Detect)
  :fDetector(Detect)
{
  fDetectorDir  = new G4UIdirectory("/BBHodoG4MC/detector/");
  fDetectorDir->SetGuidance("Detector geometry control");

  fUpdateCmd = new G4UIcommand("/BBHodoG4MC/detector/update",this);
  fUpdateCmd->SetGuidance("Update the detector geometry with changed values.");
  fUpdateCmd->SetGuidance("Must be run before beamOn if detector has been changed.");  
}

//---------------------------------------------------------------------------

DetectorMessenger::~DetectorMessenger()
{;}

//---------------------------------------------------------------------------

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 

  if(command == fUpdateCmd)
    fDetector->UpdateGeometry();

}

//---------------------------------------------------------------------------
