
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundTestArrResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMSPlaygroundTestArrResponseLibrary::MSPlaygroundTestArrResponseToJsonString(const UMSPlaygroundTestArrResponse* Serializable, const bool Pretty)
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

UMSPlaygroundTestArrResponse* UMSPlaygroundTestArrResponseLibrary::Make(TArray<int32> Value, UObject* Outer)
{
	auto Serializable = NewObject<UMSPlaygroundTestArrResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UMSPlaygroundTestArrResponseLibrary::Break(const UMSPlaygroundTestArrResponse* Serializable, TArray<int32>& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Value = Serializable->Value;
	}
		
}

