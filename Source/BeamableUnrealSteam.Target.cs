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
				if(!File.Exists(iniPath))
				{
					Console.WriteLine($"Could not find {iniPath} to set up steam_appid.txt");
					return;
				}
				
				Console.WriteLine($"Reading ini file at {iniPath} to set up steam_appid.txt");
				var iniContents = File.ReadAllLines(iniPath);
				if(!iniContents.Any(c => c.StartsWith("SteamDevAppId"))) return;
				
				
				var steamAppIdLine = iniContents.First(c => c.StartsWith("SteamDevAppId"));
				var steamAppId = steamAppIdLine[(steamAppIdLine.LastIndexOf('=') + 1)..].TrimEnd();
				Console.WriteLine($"Found steam app id ({steamAppId}) at ini file {iniPath}. Setting up.");

				if (Platform == UnrealTargetPlatform.Win64)
				{
					Console.WriteLine($"Preparing Windows PostBuildSteps.");
					string WinPath = Path.Combine(basePath, "Windows", "steam_appid.txt");
					string WinDir = Path.GetDirectoryName(WinPath);
					PostBuildSteps.Add($"if not exist \"{WinDir}\" mkdir \"{WinDir}\"");
					PostBuildSteps.Add($"echo {steamAppId}> \"{WinPath}\"");
					PostBuildSteps.Add($"echo Steam App ID content: && type \"{WinPath}\"");
				}
				else if (Platform == UnrealTargetPlatform.Mac)
				{
					string MacPath = Path.Combine(basePath, "Mac", $"{Name}.app", "Contents", "UE", Name, "Binaries", "Mac", "steam_appid.txt");
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
