#pragma once
#include "BeamLogging.h"
#include "BeamPIEConfig.h"
#include "Misc/DefaultValueHelper.h"

class FBeamPIE_Utilities
{
public:
	static bool GetPIEInstanceFromCommandLine(int& Instance)
	{
		Instance = -1;
		FString GameUserSettingIni;
					
		if (FParse::Value(FCommandLine::Get(), TEXT("GameUserSettingsINI="), GameUserSettingIni, false))
		{
			auto InstanceStr = GameUserSettingIni.Replace(TEXT("PIEGameUserSettings"), TEXT(""));
			if (!FDefaultValueHelper::ParseInt(InstanceStr, Instance))
			{
				UE_LOG(LogBeamEditor, Error, TEXT("Error on parse the override instance for the STR: %s"), *InstanceStr);
				return false;
			}
		}else
		{
			return false;
		}

		return true;
	}

	
	static bool CheckPIEMapFilter(FString MapName, FBeamPIE_Settings PIESetting)
	{
		FRegexMatcher Regex = FRegexMatcher(FRegexPattern(PIESetting.AllowedMapNamePattern), MapName);
		if (Regex.FindNext())
		{
			if (PIESetting.AllowedInMaps.Num() != 0)
			{
				for (auto MapWorld : PIESetting.AllowedInMaps)
				{
					FString WorldName = MapWorld.GetAssetName();
					if (WorldName.Contains(MapName))
					{
						return true;
					}
				}
			}else
			{
				return true;
			}
		}
		return false;
	} 

	/**
	 * This will return either @link FWorldContext::PIEInstance @endlink or the Instance based on whether we've
	 * extracted from the CLArgs Unreal passes to separate-process-PIEs.
	 */
	static int32 GetPIEInstance(FWorldContext* WorldContext)
	{
		if (WorldContext == nullptr)
		{
			return -1;
		}
		int Instance;
#if WITH_EDITOR
		// If is running in the engine but in a different process
		if (WorldContext && (WorldContext->WorldType == EWorldType::PIE || WorldContext->WorldType == EWorldType::Game))
		{
			if (!GEngine->IsEditor() || (WorldContext->PIEInstance == 0 && !IsRunningOnServer(WorldContext->World())))
			{
				// If its running in a different process we get the PIE instance from the command line
				if (GetPIEInstanceFromCommandLine(Instance))
				{
					return Instance + 1;
				}else // If there's no command line so that means it is the one running in the unreal or the index 0
				{
					return 	1;
				}
			}
		}
#endif
		
		return WorldContext->PIEInstance;
	}

	/**
	 * Return true it's running on any type of server instance
	 */
	static bool IsRunningOnServer(UWorld* World)
	{
		return World->GetNetMode() < NM_Client && World->GetNetMode() != NM_Standalone;
	}

	/**
	 * This fixes the PIE instance for all the cases of running in 
	 */
	static bool GetNamespacedUserSlotForPIE(const UObject* CallingContext, FUserSlot UserSlot, FString& PIESlotName)
	{
#if WITH_EDITOR
		// If we are already a namespaced name, we just return it.
		if (UserSlot.Name.StartsWith("PIE_"))
		{
			PIESlotName = UserSlot;
			return true;
		}

		if (CallingContext && GEngine)
		{
			const auto WorldContext = GEngine->GetWorldContextFromWorld(CallingContext->GetWorld());
		
			// Check if the process it is running in a different process, if so we need to get the PIE instance from the command line
			if (WorldContext && (WorldContext->WorldType == EWorldType::PIE || WorldContext->WorldType == EWorldType::Game))
			{
				// When we are running in a different process for multiples PIE instances the first one starts on the instance 0
				// But for running under the same process the first starts on 1
				// Also the GEngine->IsEditor is false for other instances but for 0 it's true, so we need to check if the instance
				// is zero and is not the server (which is also 0 for different process)
				if (!GEngine->IsEditor() || (WorldContext->PIEInstance == 0 && !FBeamPIE_Utilities::IsRunningOnServer(WorldContext->World())))
				{
					int PIEInstance;
					if (FBeamPIE_Utilities::GetPIEInstanceFromCommandLine(PIEInstance))
					{
						PIEInstance += 1;
					}else
					{
						PIEInstance = 1;
					}
					PIESlotName = FString::Printf(TEXT("PIE_%d_%s"), PIEInstance, *UserSlot.Name);
				}else
				{
					PIESlotName = FString::Printf(TEXT("PIE_%d_%s"), WorldContext->PIEInstance, *UserSlot.Name);
				}
				return true;
			}
		}
#endif
		
		return false;
	}
};


