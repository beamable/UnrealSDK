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

		// iOS-specific post-build setup with Apple signing integration
		if (Type == TargetType.Game)
		{
			var packageOutputDir = Path.Combine(ProjectFile.Directory.FullName, "Build/iOS");
			string basePath = !string.IsNullOrEmpty(packageOutputDir) ? packageOutputDir : "";
			Console.WriteLine($"Setting up Platform - iOS with Apple Signing - {basePath}");

			if (!string.IsNullOrEmpty(basePath))
			{
				var iniPath = Path.Combine(ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");

				if (File.Exists(iniPath))
				{
					var iniContents = File.ReadAllLines(iniPath);
					
					// Read Apple OAuth configuration
					var appleClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("AppleClientId"));
					var appleTeamIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("AppleTeamId"));
					var appleBundleIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("AppleBundleId"));

					// Setup Apple configuration for iOS
					if (appleClientIdLine != null && appleTeamIdLine != null && appleBundleIdLine != null)
					{
						var appleClientId = appleClientIdLine[(appleClientIdLine.LastIndexOf('=') + 1)..].TrimEnd();
						var appleTeamId = appleTeamIdLine[(appleTeamIdLine.LastIndexOf('=') + 1)..].TrimEnd();
						var appleBundleId = appleBundleIdLine[(appleBundleIdLine.LastIndexOf('=') + 1)..].TrimEnd();

						string appleConfigContent = $"{{\"apple_client_id\":\"{appleClientId}\",\"apple_team_id\":\"{appleTeamId}\",\"apple_bundle_id\":\"{appleBundleId}\"}}";

						if (Platform == UnrealTargetPlatform.IOS)
						{
							string iosPath = Path.Combine(basePath, "iOS", $"{Name}.app", "appleconfig.json");
							PostBuildSteps.Add(string.Format("mkdir -p \"$(dirname '{1}')\" && echo '{0}' > \"{1}\"", appleConfigContent, iosPath));
						}
					}
				}
			}
		}
	}
}
