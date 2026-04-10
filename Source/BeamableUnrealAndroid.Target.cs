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
		Console.WriteLine($"[DEBUG] Constructor started - Platform: {Platform}, Type: {Type}");

		// Android-specific post-build setup with Google signing integration
		if (Type == TargetType.Game && Platform == UnrealTargetPlatform.Android)
		{
			var iniPath = Path.Combine(ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");
			UpdateEngineIniForAndroid(iniPath);
		}
	}

	/// <summary>
	/// Updates DefaultEngine.ini with Android-specific configuration including:
	/// - OnlineSubsystemGoogle ClientId replacement with Android-specific value
	/// - Google as default platform service
	/// </summary>
	/// <param name="iniPath">Path to DefaultEngine.ini file</param>
	private void UpdateEngineIniForAndroid(string iniPath)
	{
		Console.WriteLine($"[DEBUG] INI Path: {iniPath}");
		
		if (!File.Exists(iniPath))
		{
			Console.WriteLine($"[WARNING] DefaultEngine.ini not found at {iniPath}");
			return;
		}

		var iniContents = File.ReadAllLines(iniPath).ToList();

		// Read Google OAuth configuration for Android
		var googleClientIdLine = iniContents.FirstOrDefault(c => c.Trim().Contains("ClientId-Android"));
		
		if (googleClientIdLine == null)
		{
			Console.WriteLine($"[WARNING] ClientId-Android not found in DefaultEngine.ini");
			return;
		}

		// Extract the Android ClientId value
		var androidClientId = googleClientIdLine.Split('=')[1].Trim();
		Console.WriteLine($"[DEBUG] Found Android ClientId: {androidClientId}");
		Console.WriteLine($"[DEBUG] Found Google configuration - processing INI updates");

		// Process INI file updates
		ProcessIniSections(iniContents, androidClientId);
		
		// Write updated ini file
		File.WriteAllLines(iniPath, iniContents);
		Console.WriteLine($"[DEBUG] Wrote the configs for Google Sign In to DefaultEngine.ini with {iniContents.Count} lines.");
	}

	/// <summary>
	/// Processes and updates all relevant sections in the INI file
	/// </summary>
	private void ProcessIniSections(System.Collections.Generic.List<string> iniContents, string androidClientId)
	{
		// Update OnlineSubsystem section
		UpdateOrInsertIniValue(iniContents, "[OnlineSubsystem]", "DefaultPlatformService", "Google");
		UpdateOrInsertIniValue(iniContents, "[OnlineSubsystem]", "NativePlatformService", "Google");
		
		// Update OnlineSubsystemGoogle section with Android ClientId
		UpdateOrInsertIniValue(iniContents, "[OnlineSubsystemGoogle]", "ClientId", androidClientId);
	}

	/// <summary>
	/// Updates or inserts a key-value pair in the specified INI section.
	/// If the key exists, it updates the value. If not, it inserts at the end of the section.
	/// </summary>
	/// <param name="iniContents">The INI file contents as a list of lines</param>
	/// <param name="sectionName">The section name (e.g., "[OnlineSubsystem]")</param>
	/// <param name="key">The key to update or insert (e.g., "DefaultPlatformService")</param>
	/// <param name="value">The value to set</param>
	/// <param name="comment">Optional comment to add above the key-value pair</param>
	private void UpdateOrInsertIniValue(System.Collections.Generic.List<string> iniContents, string sectionName, string key, string value, string comment = null)
	{
		int sectionIndex = -1;
		int keyIndex = -1;
		int sectionEndIndex = -1;
		bool inSection = false;

		// Find the section, check if key exists, and find section end
		for (int i = 0; i < iniContents.Count; i++)
		{
			if (iniContents[i].Trim() == sectionName)
			{
				sectionIndex = i;
				inSection = true;
				continue;
			}

			if (inSection)
			{
				// Check if we found the key
				if (iniContents[i].Trim().StartsWith($"{key}="))
				{
					keyIndex = i;
					inSection = false;
					break;
				}

				// If we hit another section, mark the end and stop looking
				if (iniContents[i].Trim().StartsWith("["))
				{
					sectionEndIndex = i;
					inSection = false;
					break;
				}
			}
		}

		// If we're still in section at end of file, mark end as last line
		if (inSection)
		{
			sectionEndIndex = iniContents.Count;
		}

		// If section doesn't exist, create it at the end
		if (sectionIndex == -1)
		{
			iniContents.Add("");
			iniContents.Add(sectionName);
			if (!string.IsNullOrEmpty(comment))
			{
				iniContents.Add(comment);
			}
			iniContents.Add($"{key}={value}");
			Console.WriteLine($"[DEBUG] Created section {sectionName} with {key}={value}");
			return;
		}

		// If key exists, update it
		if (keyIndex != -1)
		{
			iniContents[keyIndex] = $"{key}={value}";
			Console.WriteLine($"[DEBUG] Updated {key} in {sectionName}");
		}
		else
		{
			// Key doesn't exist, insert at the end of the section (before next section or at file end)
			int insertIndex = sectionEndIndex;
			if (!string.IsNullOrEmpty(comment))
			{
				iniContents.Insert(insertIndex, comment);
				insertIndex++;
			}
			iniContents.Insert(insertIndex, $"{key}={value}");
			Console.WriteLine($"[DEBUG] Inserted {key}={value} at end of {sectionName}");
		}
	}
}
