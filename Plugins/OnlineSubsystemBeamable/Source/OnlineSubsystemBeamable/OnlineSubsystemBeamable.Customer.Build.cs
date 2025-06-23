// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

using System;
using UnrealBuildTool;

public partial class OnlineSubsystemBeamable : ModuleRules
{
	private partial void CustomerExtension(ReadOnlyTargetRules Target)
	{
		// Inject an implementation for that inherits the FOnlineSubsystemBeamable implementation
		// You can override the Init function to configure the various hooks we expose. Don't forget to call the parent version.
		// You can override Exec, if you wish, to expose functionality outside of the IOnlineSubsystem interfaces to your game without depending directly on Beamable (we advise you to
		// just take on the dependency at this point).
		
		
		// Use the microservice clients in here.
		// BeamableUnrealMicroserviceClients.AddMicroserviceClients(this);
	}
	
}