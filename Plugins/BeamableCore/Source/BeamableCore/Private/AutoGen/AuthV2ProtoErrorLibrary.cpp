
#include "BeamableCore/Public/AutoGen/AuthV2ProtoErrorLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ProtoErrorLibrary::AuthV2ProtoErrorToJsonString(const UAuthV2ProtoError* Serializable, const bool Pretty)
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

UAuthV2ProtoError* UAuthV2ProtoErrorLibrary::Make(FOptionalInt32 Status, FOptionalString Error, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ProtoError>(Outer);
	Serializable->Status = Status;
	Serializable->Error = Error;
	Serializable->Description = Description;
	
	return Serializable;
}

void UAuthV2ProtoErrorLibrary::Break(const UAuthV2ProtoError* Serializable, FOptionalInt32& Status, FOptionalString& Error, FOptionalString& Description)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Status = Serializable->Status;
		Error = Serializable->Error;
		Description = Serializable->Description;
	}
		
}

