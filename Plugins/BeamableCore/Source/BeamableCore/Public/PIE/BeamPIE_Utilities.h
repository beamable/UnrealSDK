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
		if (GEngine->IsEditor() )
		{
			bool HasServer = false;
			const auto& Contexts = GEngine->GetWorldContexts();
			for (const auto& Context : Contexts)
			{
				HasServer |= IsRunningOnServer(Context.World());
			}
			
			if (HasServer)
			{
				return WorldContext->PIEInstance;
			}else
			{
				return WorldContext->PIEInstance + 1;
			}
		}else
		{
			if (GetPIEInstanceFromCommandLine(Instance) && !IsRunningOnServer(WorldContext->World()))
			{
				return Instance + 1;
			}else 
			{
				// This is the server
				return 0;
			}
		}
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

			if (WorldContext && (WorldContext->WorldType == EWorldType::PIE || WorldContext->WorldType == EWorldType::Game))
			{
				auto PIEInstance = GetPIEInstance(WorldContext);	
				PIESlotName = FString::Printf(TEXT("PIE_%d_%s"), PIEInstance, *UserSlot.Name);
		
				return true;
			}
		}
#endif
		
		return false;
	}
};


