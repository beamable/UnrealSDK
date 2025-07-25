
#include "BeamableCore/Public/AutoGen/AvailabilityRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAvailabilityRequestBodyLibrary::AvailabilityRequestBodyToJsonString(const UAvailabilityRequestBody* Serializable, const bool Pretty)
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

UAvailabilityRequestBody* UAvailabilityRequestBodyLibrary::Make(EBeamGroupType Type, FOptionalBool bSubGroup, FOptionalString Name, FOptionalString Tag, UObject* Outer)
{
	auto Serializable = NewObject<UAvailabilityRequestBody>(Outer);
	Serializable->Type = Type;
	Serializable->bSubGroup = bSubGroup;
	Serializable->Name = Name;
	Serializable->Tag = Tag;
	
	return Serializable;
}

void UAvailabilityRequestBodyLibrary::Break(const UAvailabilityRequestBody* Serializable, EBeamGroupType& Type, FOptionalBool& bSubGroup, FOptionalString& Name, FOptionalString& Tag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Type = Serializable->Type;
		bSubGroup = Serializable->bSubGroup;
		Name = Serializable->Name;
		Tag = Serializable->Tag;
	}
		
}

