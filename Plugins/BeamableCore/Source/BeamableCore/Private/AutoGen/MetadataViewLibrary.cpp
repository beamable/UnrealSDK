
#include "BeamableCore/Public/AutoGen/MetadataViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMetadataViewLibrary::MetadataViewToJsonString(const UMetadataView* Serializable, const bool Pretty)
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

UMetadataView* UMetadataViewLibrary::Make(bool bCohorted, bool bFrozen, bool bPartitioned, FString ParentLeaderboard, FOptionalInt64 FreezeTime, FOptionalLeaderboardCohortSettings CohortSettings, FOptionalBeamClientPermission Permissions, FOptionalInt32 MaxEntries, FOptionalInt64 Expiration, FOptionalArrayOfString Derivatives, UObject* Outer)
{
	auto Serializable = NewObject<UMetadataView>(Outer);
	Serializable->bCohorted = bCohorted;
	Serializable->bFrozen = bFrozen;
	Serializable->bPartitioned = bPartitioned;
	Serializable->ParentLeaderboard = ParentLeaderboard;
	Serializable->FreezeTime = FreezeTime;
	Serializable->CohortSettings = CohortSettings;
	Serializable->Permissions = Permissions;
	Serializable->MaxEntries = MaxEntries;
	Serializable->Expiration = Expiration;
	Serializable->Derivatives = Derivatives;
	
	return Serializable;
}

void UMetadataViewLibrary::Break(const UMetadataView* Serializable, bool& bCohorted, bool& bFrozen, bool& bPartitioned, FString& ParentLeaderboard, FOptionalInt64& FreezeTime, FOptionalLeaderboardCohortSettings& CohortSettings, FOptionalBeamClientPermission& Permissions, FOptionalInt32& MaxEntries, FOptionalInt64& Expiration, FOptionalArrayOfString& Derivatives)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bCohorted = Serializable->bCohorted;
		bFrozen = Serializable->bFrozen;
		bPartitioned = Serializable->bPartitioned;
		ParentLeaderboard = Serializable->ParentLeaderboard;
		FreezeTime = Serializable->FreezeTime;
		CohortSettings = Serializable->CohortSettings;
		Permissions = Serializable->Permissions;
		MaxEntries = Serializable->MaxEntries;
		Expiration = Serializable->Expiration;
		Derivatives = Serializable->Derivatives;
	}
		
}

