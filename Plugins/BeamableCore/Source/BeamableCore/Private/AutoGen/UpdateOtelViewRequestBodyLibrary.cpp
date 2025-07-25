
#include "BeamableCore/Public/AutoGen/UpdateOtelViewRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateOtelViewRequestBodyLibrary::UpdateOtelViewRequestBodyToJsonString(const UUpdateOtelViewRequestBody* Serializable, const bool Pretty)
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

UUpdateOtelViewRequestBody* UUpdateOtelViewRequestBodyLibrary::Make(FOptionalBool bIsFavorite, FOptionalBool bIsPublic, FOptionalString Name, FOptionalString Query, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateOtelViewRequestBody>(Outer);
	Serializable->bIsFavorite = bIsFavorite;
	Serializable->bIsPublic = bIsPublic;
	Serializable->Name = Name;
	Serializable->Query = Query;
	
	return Serializable;
}

void UUpdateOtelViewRequestBodyLibrary::Break(const UUpdateOtelViewRequestBody* Serializable, FOptionalBool& bIsFavorite, FOptionalBool& bIsPublic, FOptionalString& Name, FOptionalString& Query)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsFavorite = Serializable->bIsFavorite;
		bIsPublic = Serializable->bIsPublic;
		Name = Serializable->Name;
		Query = Serializable->Query;
	}
		
}

