
#include "BeamableCore/Public/AutoGen/ProtoErrorLibrary.h"

#include "CoreMinimal.h"


FString UProtoErrorLibrary::ProtoErrorToJsonString(const UProtoError* Serializable, const bool Pretty)
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

UProtoError* UProtoErrorLibrary::Make(FOptionalInt32 Status, FOptionalString Error, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<UProtoError>(Outer);
	Serializable->Status = Status;
	Serializable->Error = Error;
	Serializable->Description = Description;
	
	return Serializable;
}

void UProtoErrorLibrary::Break(const UProtoError* Serializable, FOptionalInt32& Status, FOptionalString& Error, FOptionalString& Description)
{
	Status = Serializable->Status;
	Error = Serializable->Error;
	Description = Serializable->Description;
		
}

