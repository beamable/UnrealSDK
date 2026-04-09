// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Linq;

public class BeamableUnrealAndroidTarget : BeamableUnrealTarget
{
	public BeamableUnrealAndroidTarget(TargetInfo Target) : base(Target)
	{
		// Set up a Global define so that we can cut code out of non-Android builds
		GlobalDefinitions.Add("IS_ANDROID_DISTRIBUTION=1");

		// Android-specific post-build setup with Google signing integration
		if (Type == TargetType.Game)
		{
			var packageOutputDir = Path.Combine(ProjectFile.Directory.FullName, "Build/Android");
			string basePath = !string.IsNullOrEmpty(packageOutputDir) ? packageOutputDir : "";
			Console.WriteLine($"Setting up Platform - Android with Google Signing - {basePath}");

			if (!string.IsNullOrEmpty(basePath))
			{
				var iniPath = Path.Combine(ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");

				if (File.Exists(iniPath))
				{
					var iniContents = File.ReadAllLines(iniPath).ToList();
					
					// Read Google OAuth configuration for Android
					var googleClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("ClientId-Android"));
					var googleServerClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("ServerClientId-Android"));

					// Setup Google configuration for Android
					if (googleClientIdLine != null && googleServerClientIdLine != null)
					{
						if (Platform == UnrealTargetPlatform.Android)
						{
							// Update DefaultEngine.ini to set Android as default online subsystem
							bool foundOnlineSubsystemSection = false;
							bool updatedDefaultPlatform = false;
							
							for (int i = 0; i < iniContents.Count; i++)
							{
								if (iniContents[i].Trim() == "[OnlineSubsystem]")
								{
									foundOnlineSubsystemSection = true;
								}
								else if (foundOnlineSubsystemSection && iniContents[i].Trim().StartsWith("DefaultPlatformService="))
								{
									iniContents[i] = "DefaultPlatformService=Google";
									updatedDefaultPlatform = true;
									break;
								}
								else if (foundOnlineSubsystemSection && iniContents[i].Trim().StartsWith("["))
								{
									// Hit next section without finding DefaultPlatformService
									iniContents.Insert(i, "DefaultPlatformService=Google");
									updatedDefaultPlatform = true;
									break;
								}
							}
							
							// If [OnlineSubsystem] section doesn't exist, add it
							if (!foundOnlineSubsystemSection)
							{
								iniContents.Add("");
								iniContents.Add("[OnlineSubsystem]");
								iniContents.Add("DefaultPlatformService=Google");
								iniContents.Add("NativePlatformService=Google");
							}
							else if (!updatedDefaultPlatform)
							{
								// Section exists but no DefaultPlatformService found, add at end
								iniContents.Add("DefaultPlatformService=Google");
							}
							
							// Write updated ini file
							File.WriteAllLines(iniPath, iniContents);
						}
					}
				}
			}
		}
	}
}
