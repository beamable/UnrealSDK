
#include "BeamableCore/Public/AutoGen/LeaderboardCreateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardCreateRequestBodyLibrary::LeaderboardCreateRequestBodyToJsonString(const ULeaderboardCreateRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

ULeaderboardCreateRequestBody* ULeaderboardCreateRequestBodyLibrary::Make(bool bSharded, FOptionalBool bPartitioned, FOptionalInt64 FreezeTime, FOptionalString ScoreName, FOptionalLeaderboardCohortSettings CohortSettings, FOptionalBeamClientPermission Permissions, FOptionalInt32 MaxEntries, FOptionalInt64 Ttl, FOptionalArrayOfString Derivatives, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardCreateRequestBody>(Outer);
	Serializable->bSharded = bSharded;
	Serializable->bPartitioned = bPartitioned;
	Serializable->FreezeTime = FreezeTime;
	Serializable->ScoreName = ScoreName;
	Serializable->CohortSettings = CohortSettings;
	Serializable->Permissions = Permissions;
	Serializable->MaxEntries = MaxEntries;
	Serializable->Ttl = Ttl;
	Serializable->Derivatives = Derivatives;
	
	return Serializable;
}

void ULeaderboardCreateRequestBodyLibrary::Break(const ULeaderboardCreateRequestBody* Serializable, bool& bSharded, FOptionalBool& bPartitioned, FOptionalInt64& FreezeTime, FOptionalString& ScoreName, FOptionalLeaderboardCohortSettings& CohortSettings, FOptionalBeamClientPermission& Permissions, FOptionalInt32& MaxEntries, FOptionalInt64& Ttl, FOptionalArrayOfString& Derivatives)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSharded = Serializable->bSharded;
		bPartitioned = Serializable->bPartitioned;
		FreezeTime = Serializable->FreezeTime;
		ScoreName = Serializable->ScoreName;
		CohortSettings = Serializable->CohortSettings;
		Permissions = Serializable->Permissions;
		MaxEntries = Serializable->MaxEntries;
		Ttl = Serializable->Ttl;
		Derivatives = Serializable->Derivatives;
	}
		
}

