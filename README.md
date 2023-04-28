------------------------------------------------------------------------

 BBHodoG4MC: a Geant4 framework for simulating BBHodo 

------------------------------------------------------------------------

	http://github.com/dhamilton-glasgow/BBHodoG4MC
	(developed and tested with Geant4.10.4 and root6.22 on centos7)

------------------------------------------------------------------------
 Compilation

	mkdir build
  	cd build
  	cmake ../ (or cmake3 ../ on some systems)
  	make -jX (X specifies number of cores to use)

------------------------------------------------------------------------
 Running the simulation in visualisation mode

  	./BBHodoG4MC
  	then in the gui: 
	/control/execute macros/vis_beam.mac 

------------------------------------------------------------------------
 Running the simulation in batch mode

  	./BBHodoG4MC macros/batch_beam.mac 

------------------------------------------------------------------------
 PhysicsList options (always call in macro before /run/initialize)

  	/BBHodoG4MC/physics/addPhysics 
  	Add physics list (standard_opt3, QGSP_BIC_EMY, QGSP_BIS_HP, QGSP_BERT_HP, FTFP_BERT_HP)

------------------------------------------------------------------------
 Generator options 

  	/BBHodoG4MC/generator/Mode 
  	Set the mode of the generator (0 for BEAM or 1 for ROOT)

  	BEAM mode using geant4 gps to generate beam of particles.
  	ROOT mode requires a root file with a tree called TGen, which contains branches:

		Nparticles	-- number of primary particles in this event
  		weight		-- event weight (for consistency this should be per uA beam current)
		flag		-- an integer to represent generator (reaction) type, ie elastic=1
		vx[Nparticles]	-- vertex position vector (cm)
		vy[Nparticles]
		vz[Nparticles]
		px[Nparticles]	-- momentum 3-vector (MeV/c)
		py[Nparticles]
		pz[Nparticles]
		E[Nparticles]	-- energy in MeV
		pdg[Nparticles]	-- pdg code

	/BBHodoG4MC/generator/Nevents
	Set the number of primary events to be generated

  	/BBHodoG4MC/generator/InputFile
  	Set the full name and path of the file with the input ROOT ntuple (in ROOT mode)  

------------------------------------------------------------------------
 OutputManager options 

  	/BBHodoG4MC/output/setOutputFile
  	Set the full name and path of the output file

  	The output tree is called TOut and has the following branches:
		Event_weight	-- event weight (for consistency this should be per uA beam current)
		Event_flag	-- an integer to represent generator (reaction) type, ie elastic=1
		Primary_Nhits	-- number of primary particles in this event
		Primary_*[]	-- arrays of primary variables, including pdg, energy, position, direction
		Virtual_Nhits	-- number of virtual detector hits in this event
		Virtual_*[]	-- arrays of virtual hit variables, including pdg, energy, position, direction,
				   particle vertex, time, track id, mother track id and detector id variables:
					Virtual_det[] -- which detector (0) 
					Virtual_mod[] -- which sector (0)
					Virtual_row[] -- which row (0-90)
					Virtual_col[] -- which col (1)
		Real_Nhits	-- number of real detector hits in this event
		Real_*[]	-- arrays of real hit variables, including energy deposit, position, time,
				   and detector id variables:
					Real_det[] -- which detector (0) 
					Real_mod[] -- which sector (0)
					Real_row[] -- which row (0-90)
					Real_col[] -- which col (1)



