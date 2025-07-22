
#include "BeamableCore/Public/AutoGen/GamerTagLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGamerTagLibrary::GamerTagToJsonString(const UGamerTag* Serializable, const bool Pretty)
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

UGamerTag* UGamerTagLibrary::Make(int64 Tag, FString Platform, FOptionalString Alias, FOptionalInt64 Added, FOptionalSessionUser User, FOptionalArrayOfCohortEntry Trials, UObject* Outer)
{
	auto Serializable = NewObject<UGamerTag>(Outer);
	Serializable->Tag = Tag;
	Serializable->Platform = Platform;
	Serializable->Alias = Alias;
	Serializable->Added = Added;
	Serializable->User = User;
	Serializable->Trials = Trials;
	
	return Serializable;
}

void UGamerTagLibrary::Break(const UGamerTag* Serializable, int64& Tag, FString& Platform, FOptionalString& Alias, FOptionalInt64& Added, FOptionalSessionUser& User, FOptionalArrayOfCohortEntry& Trials)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tag = Serializable->Tag;
		Platform = Serializable->Platform;
		Alias = Serializable->Alias;
		Added = Serializable->Added;
		User = Serializable->User;
		Trials = Serializable->Trials;
	}
		
}

