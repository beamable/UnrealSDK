
#include "BeamableCore/Public/AutoGen/CreatePartyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreatePartyLibrary::CreatePartyToJsonString(const UCreateParty* Serializable, const bool Pretty)
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

UCreateParty* UCreatePartyLibrary::Make(FOptionalString Restriction, FOptionalBeamGamerTag Leader, FOptionalInt32 MaxSize, UObject* Outer)
{
	auto Serializable = NewObject<UCreateParty>(Outer);
	Serializable->Restriction = Restriction;
	Serializable->Leader = Leader;
	Serializable->MaxSize = MaxSize;
	
	return Serializable;
}

void UCreatePartyLibrary::Break(const UCreateParty* Serializable, FOptionalString& Restriction, FOptionalBeamGamerTag& Leader, FOptionalInt32& MaxSize)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Restriction = Serializable->Restriction;
		Leader = Serializable->Leader;
		MaxSize = Serializable->MaxSize;
	}
		
}

