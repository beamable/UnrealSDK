
#include "BeamableCore/Public/AutoGen/AvailabilityRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UAvailabilityRequestBodyLibrary::AvailabilityRequestBodyToJsonString(const UAvailabilityRequestBody* Serializable, const bool Pretty)
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

UAvailabilityRequestBody* UAvailabilityRequestBodyLibrary::Make(EGroupType Type, FOptionalBool bSubGroup, FOptionalString Name, FOptionalString Tag, UObject* Outer)
{
	auto Serializable = NewObject<UAvailabilityRequestBody>(Outer);
	Serializable->Type = Type;
	Serializable->bSubGroup = bSubGroup;
	Serializable->Name = Name;
	Serializable->Tag = Tag;
	
	return Serializable;
}

void UAvailabilityRequestBodyLibrary::Break(const UAvailabilityRequestBody* Serializable, EGroupType& Type, FOptionalBool& bSubGroup, FOptionalString& Name, FOptionalString& Tag)
{
	Type = Serializable->Type;
	bSubGroup = Serializable->bSubGroup;
	Name = Serializable->Name;
	Tag = Serializable->Tag;
		
}

