
#include "BeamableCore/Public/AutoGen/OtelViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOtelViewLibrary::OtelViewToJsonString(const UOtelView* Serializable, const bool Pretty)
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

UOtelView* UOtelViewLibrary::Make(FString PlayerId, FString Name, FString Query, FOptionalBool bIsFavorite, FOptionalBool bIsPublic, FOptionalObjectId Id, UObject* Outer)
{
	auto Serializable = NewObject<UOtelView>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Name = Name;
	Serializable->Query = Query;
	Serializable->bIsFavorite = bIsFavorite;
	Serializable->bIsPublic = bIsPublic;
	Serializable->Id = Id;
	
	return Serializable;
}

void UOtelViewLibrary::Break(const UOtelView* Serializable, FString& PlayerId, FString& Name, FString& Query, FOptionalBool& bIsFavorite, FOptionalBool& bIsPublic, FOptionalObjectId& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Name = Serializable->Name;
		Query = Serializable->Query;
		bIsFavorite = Serializable->bIsFavorite;
		bIsPublic = Serializable->bIsPublic;
		Id = Serializable->Id;
	}
		
}

