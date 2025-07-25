
#include "BeamableCore/Public/AutoGen/UpdatePartyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdatePartyLibrary::UpdatePartyToJsonString(const UUpdateParty* Serializable, const bool Pretty)
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

UUpdateParty* UUpdatePartyLibrary::Make(FOptionalString Restriction, FOptionalInt32 MaxSize, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateParty>(Outer);
	Serializable->Restriction = Restriction;
	Serializable->MaxSize = MaxSize;
	
	return Serializable;
}

void UUpdatePartyLibrary::Break(const UUpdateParty* Serializable, FOptionalString& Restriction, FOptionalInt32& MaxSize)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Restriction = Serializable->Restriction;
		MaxSize = Serializable->MaxSize;
	}
		
}

