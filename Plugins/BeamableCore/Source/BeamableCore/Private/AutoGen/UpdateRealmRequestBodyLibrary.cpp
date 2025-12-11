
#include "BeamableCore/Public/AutoGen/UpdateRealmRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateRealmRequestBodyLibrary::UpdateRealmRequestBodyToJsonString(const UUpdateRealmRequestBody* Serializable, const bool Pretty)
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

UUpdateRealmRequestBody* UUpdateRealmRequestBodyLibrary::Make(FOptionalBool bArchiveStatus, FOptionalBool bHiddenStatus, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateRealmRequestBody>(Outer);
	Serializable->bArchiveStatus = bArchiveStatus;
	Serializable->bHiddenStatus = bHiddenStatus;
	
	return Serializable;
}

void UUpdateRealmRequestBodyLibrary::Break(const UUpdateRealmRequestBody* Serializable, FOptionalBool& bArchiveStatus, FOptionalBool& bHiddenStatus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchiveStatus = Serializable->bArchiveStatus;
		bHiddenStatus = Serializable->bHiddenStatus;
	}
		
}

