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
					var iniContents = File.ReadAllLines(iniPath);
					
					// Read Google OAuth configuration
					var googleClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("GoogleClientId"));
					var googleServerClientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("GoogleServerClientId"));

					// Setup Google configuration for Android
					if (googleClientIdLine != null && googleServerClientIdLine != null)
					{
						var googleClientId = googleClientIdLine[(googleClientIdLine.LastIndexOf('=') + 1)..].TrimEnd();
						var googleServerClientId = googleServerClientIdLine[(googleServerClientIdLine.LastIndexOf('=') + 1)..].TrimEnd();

						string googleConfigContent = $"{{\\\"google_client_id\\\":\\\"{googleClientId}\\\",\\\"google_server_client_id\\\":\\\"{googleServerClientId}\\\"}}";

						if (Platform == UnrealTargetPlatform.Android)
						{
							string androidPath = Path.Combine(basePath, "Android", "googleconfig.json");
							string androidDir = Path.GetDirectoryName(androidPath);
							PostBuildSteps.Add($"if not exist \"{androidDir}\" mkdir \"{androidDir}\" && echo {googleConfigContent} > \"{androidPath}\"");
						}
					}
				}
			}
		}
	}
}
