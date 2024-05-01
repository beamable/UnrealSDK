#ifdef BEAM_ENABLE_BEAMABLE_OSS

#include "Customer/OnlineSubsystemHathoraDemo.h"

FString FOnlineSubsystemHathoraDemo::ConvertHathoraRegionPingsToJson(const FHathoraRegionPings& RegionPings)
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

FBeamOperationHandle FOnlineSubsystemHathoraDemo::HathoraPingsOperation(FUserSlot UserSlot)
{
	const auto Op = GetRequestTracker()->CPP_BeginOperation({UserSlot}, this->GetInstanceName().ToString(), {});

	auto PlayerAccount = GetAccountForSlot(UserSlot);
	FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda([this, PlayerAccount, UserSlot, Op](const FHathoraRegionPings& Result)
	{
		const FString PingsJson = ConvertHathoraRegionPingsToJson(Result);

		TMap<FString, FString> Stats;
		Stats.Add("wca.HathoraRegionPings", PingsJson);

		auto StatsSubsystem = GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>();

		UBeamStatUpdateCommand* Command;
		if (StatsSubsystem->TryCreateUpdateCommand(UserSlot, Stats, Command))
		{
			FBeamOperationEventHandlerCode Handler;
			Handler.BindLambda([this, Op](FBeamOperationEvent Evt)
			{
				UE_LOG(LogTemp, Display, TEXT("Updated Hathora Pings"));

				if (Evt.EventType == OET_SUCCESS)
				{
					UE_LOG_ONLINE_STATS(Display, TEXT("Updated Hathora Pings"));
					GetRequestTracker()->TriggerOperationSuccess(Op, {});
				}
				else
				{
					UE_LOG_ONLINE_STATS(Display, TEXT("Failed updateing Hathora Pings"));
					GetRequestTracker()->TriggerOperationSuccess(Op, {});
				}
			});

			StatsSubsystem->CPP_CommitStatsOperation(UserSlot, Handler);
		}
		else
		{
			UE_LOG_ONLINE_STATS(Display, TEXT("Failed updateing Hathora Pings"));
			GetRequestTracker()->TriggerOperationSuccess(Op, {});
		}
	}));

	return Op;
}

#endif
