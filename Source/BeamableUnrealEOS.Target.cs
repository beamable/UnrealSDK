// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Linq;

public class BeamableUnrealEOSTarget : BeamableUnrealTarget
{
	public BeamableUnrealEOSTarget(TargetInfo Target) : base(Target)
	{
		// Set up a Global define so that we can cut code out of non-EOS builds
		GlobalDefinitions.Add("IS_EOS_DISTRIBUTION=1");

		// EOS-specific post-build setup (works for all samples)
		if (Type == TargetType.Game)
		{
			var packageOutputDir = Path.Combine(ProjectFile.Directory.FullName, "Build/EOS");
			string basePath = !string.IsNullOrEmpty(packageOutputDir) ? packageOutputDir : "";
			Console.WriteLine($"Setting up Platform - EOS - {basePath}");

			if (!string.IsNullOrEmpty(basePath))
			{
				var iniPath = Path.Combine(ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");

				if (File.Exists(iniPath))
				{
					var iniContents = File.ReadAllLines(iniPath);
					var productIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("ProductId"));
					var sandboxIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("SandboxId"));
					var deploymentIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("DeploymentId"));
					var clientIdLine = iniContents.FirstOrDefault(c => c.Trim().StartsWith("ClientId"));

					if (productIdLine != null && sandboxIdLine != null && deploymentIdLine != null && clientIdLine != null)
					{
						var productId = productIdLine[(productIdLine.LastIndexOf('=') + 1)..].TrimEnd();
						var sandboxId = sandboxIdLine[(sandboxIdLine.LastIndexOf('=') + 1)..].TrimEnd();
						var deploymentId = deploymentIdLine[(deploymentIdLine.LastIndexOf('=') + 1)..].TrimEnd();
						var clientId = clientIdLine[(clientIdLine.LastIndexOf('=') + 1)..].TrimEnd();

						string eosConfigContent = $"{{\\\"productId\\\":\\\"{productId}\\\",\\\"sandboxId\\\":\\\"{sandboxId}\\\",\\\"deploymentId\\\":\\\"{deploymentId}\\\",\\\"clientId\\\":\\\"{clientId}\\\"}}";

						if (Platform == UnrealTargetPlatform.Win64)
						{
							string WinPath = Path.Combine(basePath, "Windows", "eosconfig.json");
							string WinDir = Path.GetDirectoryName(WinPath);
							PostBuildSteps.Add($"if not exist \"{WinDir}\" mkdir \"{WinDir}\"");
							PostBuildSteps.Add($"echo {eosConfigContent}> \"{WinPath}\"");
						}
						else if (Platform == UnrealTargetPlatform.Mac)
						{
							string MacPath = Path.Combine(basePath, "Mac", $"{Name}.app", "Contents", "MacOS", "eosconfig.json");
							string macConfigContent = $"{{\"productId\":\"{productId}\",\"sandboxId\":\"{sandboxId}\",\"deploymentId\":\"{deploymentId}\",\"clientId\":\"{clientId}\"}}";
							PostBuildSteps.Add(string.Format("mkdir -p \"$(dirname '{1}')\" && echo '{0}' > \"{1}\"", macConfigContent, MacPath));
						}
						else if (Platform == UnrealTargetPlatform.Linux)
						{
							string LinuxPath = Path.Combine(basePath, "Linux", "eosconfig.json");
							string LinuxDir = Path.GetDirectoryName(LinuxPath);
							string linuxConfigContent = $"{{\"productId\":\"{productId}\",\"sandboxId\":\"{sandboxId}\",\"deploymentId\":\"{deploymentId}\",\"clientId\":\"{clientId}\"}}";
							PostBuildSteps.Add($"mkdir -p \"{LinuxDir}\" && echo '{linuxConfigContent}' > \"{LinuxPath}\"");
						}
					}
				}
			}
		}
	}
}
