#pragma once

#include "HathoraSDK.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "UserSlots/UserSlot.h"

struct FHathoraRegionPings;

class BeamBallHathoraUtility
{
public:
	void HathoraPingsOperation(FUserSlot UserSlot, UBeamRuntime* Runtime, UBeamStatsSubsystem* Stats, FBeamOperationHandle Op)
	{
		FBeamRealmUser PlayerAccount;
		if (Runtime->TryGetSlotUserData(UserSlot, PlayerAccount))
		{
			FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda([this, UserSlot, Op, Stats, Runtime](const FHathoraRegionPings& Result)
			{
				const FString PingsJson = ConvertHathoraRegionPingsToJson(Result);

				TMap<FString, FString> StatsMap;
				StatsMap.Add("hathora_demo.pings", PingsJson);

				UBeamStatUpdateCommand* Command;
				if (Stats->TryCreateUpdateCommand(UserSlot, StatsMap, Command))
				{
					FBeamOperationEventHandlerCode Handler;
					Handler.BindLambda([this, Op, Runtime](FBeamOperationEvent Evt)
					{
						UE_LOG(LogTemp, Display, TEXT("Updated Hathora Pings"));

						if (Evt.EventType == OET_SUCCESS)
						{
							UE_LOG(LogTemp, Display, TEXT("Updated Hathora Pings"));
							Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
						}
						else
						{
							UE_LOG(LogTemp, Display, TEXT("Failed to update Hathora Pings"));
							Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
						}
					});

					Stats->CPP_CommitStatsOperation(UserSlot, Handler);
				}
				else
				{
					UE_LOG(LogTemp, Display, TEXT("Failed to update Hathora Pings"));
					Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
				}
			}));
		}
		else
		{
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});			
		}
	}

	FString ConvertHathoraRegionPingsToJson(const FHathoraRegionPings& RegionPings)
	{
		// Create a new JSON object
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		// For each pair in the Pings map, add it to the JSON object
		for (const auto& Pair : RegionPings.Pings)
		{
			JsonObject->SetNumberField(Pair.Key, Pair.Value);
		}

		// Serialize the JSON object to a string
		FString OutputString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
		if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
		{
			return OutputString;
		}

		return TEXT("{}");
	}
};
