
#include "BeamableCore/Public/AutoGen/CreatePartyLibrary.h"

#include "CoreMinimal.h"


FString UCreatePartyLibrary::CreatePartyToJsonString(const UCreateParty* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCreateParty* UCreatePartyLibrary::Make(FOptionalString Restriction, FOptionalString Leader, FOptionalInt32 MaxSize, UObject* Outer)
{
	auto Serializable = NewObject<UCreateParty>(Outer);
	Serializable->Restriction = Restriction;
	Serializable->Leader = Leader;
	Serializable->MaxSize = MaxSize;
	
	return Serializable;
}

void UCreatePartyLibrary::Break(const UCreateParty* Serializable, FOptionalString& Restriction, FOptionalString& Leader, FOptionalInt32& MaxSize)
{
	Restriction = Serializable->Restriction;
	Leader = Serializable->Leader;
	MaxSize = Serializable->MaxSize;
		
}

