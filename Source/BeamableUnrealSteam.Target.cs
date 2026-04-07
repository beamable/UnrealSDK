// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Linq;

public class BeamableUnrealSteamTarget : BeamableUnrealTarget
{
	public BeamableUnrealSteamTarget(TargetInfo Target) : base(Target)
	{
		// Set up a Global define so that we can cut code out of non-steam builds
		GlobalDefinitions.Add("IS_STEAM_DISTRIBUTION=1");

		// Steam-specific post-build setup (works for all samples)
		if (Type == TargetType.Game)
		{
			var packageOutputDir = Path.Combine(ProjectFile.Directory.FullName, "Build/Steam");
			string basePath = !string.IsNullOrEmpty(packageOutputDir) ? packageOutputDir : "";
			Console.WriteLine($"Setting up Platform - Steam - {basePath}");

			if (!string.IsNullOrEmpty(basePath))
			{
				var iniPath = Path.Combine(ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");
				var iniContents = File.ReadAllLines(iniPath);
				var steamAppIdLine = iniContents.First(c => c.StartsWith("SteamDevAppId"));
				var steamAppId = steamAppIdLine[(steamAppIdLine.LastIndexOf('=') + 1)..].TrimEnd();

				if (Platform == UnrealTargetPlatform.Win64)
				{
					string WinPath = Path.Combine(basePath, "Windows", "steam_appid.txt");
					string WinDir = Path.GetDirectoryName(WinPath);
					PostBuildSteps.Add($"if not exist \"{WinDir}\" mkdir \"{WinDir}\" && echo {steamAppId} > \"{WinPath}\"");
				}
				else if (Platform == UnrealTargetPlatform.Mac)
				{
					string MacPath = Path.Combine(basePath, "Mac", $"{Name}.app", "Contents", "MacOS", "steam_appid.txt");
					PostBuildSteps.Add(string.Format("mkdir -p \"$(dirname '{1}')\" && echo {0} > \"{1}\"", steamAppId, MacPath));
				}
				else if (Platform == UnrealTargetPlatform.Linux)
				{
					string LinuxPath = Path.Combine(basePath, "Linux", "steam_appid.txt");
					string LinuxDir = Path.GetDirectoryName(LinuxPath);
					PostBuildSteps.Add($"mkdir -p \"{LinuxDir}\" && echo {steamAppId} > \"{LinuxPath}\"");
				}
			}
		}
	}
}
