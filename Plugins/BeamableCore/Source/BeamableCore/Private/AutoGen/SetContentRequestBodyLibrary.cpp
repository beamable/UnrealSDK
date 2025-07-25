
#include "BeamableCore/Public/AutoGen/SetContentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USetContentRequestBodyLibrary::SetContentRequestBodyToJsonString(const USetContentRequestBody* Serializable, const bool Pretty)
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

USetContentRequestBody* USetContentRequestBodyLibrary::Make(UEvent* Event, FString Origin, FOptionalString RootEventId, FOptionalString OriginType, UObject* Outer)
{
	auto Serializable = NewObject<USetContentRequestBody>(Outer);
	Serializable->Event = Event;
	Serializable->Origin = Origin;
	Serializable->RootEventId = RootEventId;
	Serializable->OriginType = OriginType;
	
	return Serializable;
}

void USetContentRequestBodyLibrary::Break(const USetContentRequestBody* Serializable, UEvent*& Event, FString& Origin, FOptionalString& RootEventId, FOptionalString& OriginType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Event = Serializable->Event;
		Origin = Serializable->Origin;
		RootEventId = Serializable->RootEventId;
		OriginType = Serializable->OriginType;
	}
		
}

