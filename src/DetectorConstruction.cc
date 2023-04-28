#include "DetectorConstruction.hh"
#include "VirtualDetectorSD.hh"
#include "RealDetectorSD.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisAttributes.hh"
#include "G4String.hh"
#include "globals.hh"

#include <fstream>

using namespace CLHEP;
using namespace std;

//---------------------------------------------------------------------------

DetectorConstruction::DetectorConstruction()
{
  fNistManager  = G4NistManager::Instance();
  fDetMessenger = new DetectorMessenger(this);
}

//---------------------------------------------------------------------------

DetectorConstruction::~DetectorConstruction() 
{
  delete fDetMessenger;
}

//---------------------------------------------------------------------------

G4VPhysicalVolume* DetectorConstruction::Construct()
{ 

  G4int SDcount = 1;

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  //---------------------------------------------------------------------------
  // Create experimental hall
  //---------------------------------------------------------------------------
  
  G4Box* expHall_box = new G4Box("expHall_box",
				 2. *m, 2. *m, 2.5 *m );
  
  
  fexpHall_log = new G4LogicalVolume(expHall_box,
				     fNistManager->FindOrBuildMaterial("G4_AIR"),  
				     "expHall_log", 0, 0, 0);
  
  fExpHall = new G4PVPlacement(0, G4ThreeVector(),
			       fexpHall_log, "expHall", 0, false, 0);
  
  //--------------------------------------------------------------------------- 
  // Create BB hodoscope
  //--------------------------------------------------------------------------- 
  
  G4int    nhodo  = 90;

  G4double hodo_X = 25.*mm; 
  G4double hodo_Y = 25.*mm; 
  G4double hodo_Z = 600.*mm;
  
  G4Box* hodo_solid = new G4Box("hodo_solid", 0.5*hodo_X, 0.5*hodo_Y, 0.5*hodo_Z);
  
  G4LogicalVolume* hodo_log = new G4LogicalVolume(hodo_solid,
						  fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"),
						  "hodo_log");
  
  G4RotationMatrix* rm1 = new G4RotationMatrix();     
  rm1->rotateY(90*deg); 
  char stmp[50];
  for( int ih=0 ; ih < nhodo ; ih++ ) {
    
    sprintf( stmp, "hodo%d", SDcount );
    
    fDetVol[SDcount] = new G4PVPlacement(rm1, G4ThreeVector( 0, -1125+(ih*25*mm), 1.0 *m),
					 hodo_log, stmp, fexpHall_log, false, SDcount); 
    SDcount++;
    
  }
  
  G4double preshower_X = 90.*mm; 
  G4double preshower_Y = nhodo*25.*mm; 
  G4double preshower_Z = 600.*mm;

  G4Box* preshower_solid = new G4Box("preshower_solid", 0.5*preshower_X, 0.5*preshower_Y, 0.5*preshower_Z);
  
  G4LogicalVolume* preshower_log = new G4LogicalVolume(preshower_solid,
						   fNistManager->FindOrBuildMaterial("G4_GLASS_LEAD"),
						   "preshower_log");

  new G4PVPlacement(rm1, G4ThreeVector( 0, 0, (100-15.9+1.25-4.5)*cm ),
		    preshower_log, "preshower", fexpHall_log, false, 0); 
  
  //---------------------------------------------------------------------------
  // Set Logical Attributes
  //---------------------------------------------------------------------------

  // Senstive detector
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  
  fVirtualDetectorSD = new VirtualDetectorSD("VirtualDetectorSD", fNSD );
  SDman->AddNewDetector( fVirtualDetectorSD );
  hodo_log->SetSensitiveDetector( fVirtualDetectorSD );

  fRealDetectorSD = new RealDetectorSD("RealDetectorSD", fNSD );
  SDman->AddNewDetector( fRealDetectorSD );
  hodo_log->SetSensitiveDetector( fVirtualDetectorSD );

  // Visualisation
  G4VisAttributes* blue    = new G4VisAttributes( G4Colour(0.0,0.0,1.0) );
  G4VisAttributes* magenta = new G4VisAttributes( G4Colour(1.0,0.0,1.0) );
  
  preshower_log->SetVisAttributes(magenta);
  hodo_log->SetVisAttributes(blue);

  fexpHall_log->SetVisAttributes(G4VisAttributes::Invisible);

  //---------------------------------------------------------------------------

  return fExpHall;

}

//---------------------------------------------------------------------------

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

//---------------------------------------------------------------------------

