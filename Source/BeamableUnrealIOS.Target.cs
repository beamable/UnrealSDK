// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Linq;

public class BeamableUnrealIOSTarget : BeamableUnrealTarget
{
	public BeamableUnrealIOSTarget(TargetInfo Target) : base(Target)
	{
		// Set up a Global define so that we can cut code out of non-iOS builds
		GlobalDefinitions.Add("IS_IOS_DISTRIBUTION=1");
		Console.WriteLine($"[DEBUG] Constructor started - Platform: {Platform}, Type: {Type}");


		// iOS-specific post-build setup with Apple signing integration
		if (Type == TargetType.Game)
		{
			var packageOutputDir = Path.Combine(ProjectFile.Directory.FullName, "Build/iOS");
			string basePath = !string.IsNullOrEmpty(packageOutputDir) ? packageOutputDir : "";
			Console.WriteLine($"Setting up Platform - iOS with Apple Signing - {basePath}");

			if (!string.IsNullOrEmpty(basePath))
			{
				var iniPath = Path.Combine(ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");
				Console.WriteLine($"[DEBUG] INI Path: {iniPath}");
				if (File.Exists(iniPath))
				{
					var iniContents = File.ReadAllLines(iniPath).ToList();

					// Read Apple OAuth configuration for iOS
					var appleClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("ClientId-iOS"));
					var appleServerClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("ServerClientId-iOS"));

					// Setup Apple configuration for iOS
					if (appleClientIdLine != null && appleServerClientIdLine != null)
					{
						
						// Read additional Apple configuration (keep existing logic if needed)
						var appleTeamIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("AppleTeamId"));
						var appleBundleIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("AppleBundleId"));

						if (appleTeamIdLine != null && appleBundleIdLine != null)
						{
							if (Platform == UnrealTargetPlatform.IOS)
							{
								Console.WriteLine($"[DEBUG] Found Apple config: {appleClientIdLine != null}");

								// Update DefaultEngine.ini to set Apple as default online subsystem
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
										iniContents[i] = "DefaultPlatformService=Apple";
										updatedDefaultPlatform = true;
										break;
									}
									else if (foundOnlineSubsystemSection && iniContents[i].Trim().StartsWith("["))
									{
										// Hit next section without finding DefaultPlatformService
										iniContents.Insert(i, "DefaultPlatformService=Apple");
										updatedDefaultPlatform = true;
										break;
									}
								}

								// If [OnlineSubsystem] section doesn't exist, add it
								if (!foundOnlineSubsystemSection)
								{
									iniContents.Add("");
									iniContents.Add("[OnlineSubsystem]");
									iniContents.Add("DefaultPlatformService=Apple");
									iniContents.Add("NativePlatformService=Apple");
								}
								else if (!updatedDefaultPlatform)
								{
									// Section exists but no DefaultPlatformService found, add at end
									iniContents.Add("DefaultPlatformService=Apple");
								}
								Console.WriteLine($"[DEBUG] Wrote the configs for Apple Sign In to DefaultEngine.ini with {iniContents.Count} lines.");

								// Write updated ini file
								File.WriteAllLines(iniPath, iniContents);

							}
						}
					}
				}
			}
		}
	}
}
