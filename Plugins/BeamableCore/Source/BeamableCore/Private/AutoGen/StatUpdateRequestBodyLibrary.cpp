
#include "BeamableCore/Public/AutoGen/StatUpdateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatUpdateRequestBodyLibrary::StatUpdateRequestBodyToJsonString(const UStatUpdateRequestBody* Serializable, const bool Pretty)
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

UStatUpdateRequestBody* UStatUpdateRequestBodyLibrary::Make(FOptionalBool bEmitAnalytics, FOptionalBeamStatsType ObjectId, FOptionalMapOfString Set, FOptionalMapOfString Add, UObject* Outer)
{
	auto Serializable = NewObject<UStatUpdateRequestBody>(Outer);
	Serializable->bEmitAnalytics = bEmitAnalytics;
	Serializable->ObjectId = ObjectId;
	Serializable->Set = Set;
	Serializable->Add = Add;
	
	return Serializable;
}

void UStatUpdateRequestBodyLibrary::Break(const UStatUpdateRequestBody* Serializable, FOptionalBool& bEmitAnalytics, FOptionalBeamStatsType& ObjectId, FOptionalMapOfString& Set, FOptionalMapOfString& Add)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bEmitAnalytics = Serializable->bEmitAnalytics;
		ObjectId = Serializable->ObjectId;
		Set = Serializable->Set;
		Add = Serializable->Add;
	}
		
}

