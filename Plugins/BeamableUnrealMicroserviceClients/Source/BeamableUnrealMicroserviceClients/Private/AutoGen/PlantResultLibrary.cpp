
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlantResultLibrary::PlantResultToJsonString(const UPlantResult* Serializable, const bool Pretty)
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

UPlantResult* UPlantResultLibrary::Make(bool bSuccess, int64 PlantedAtUtcSeconds, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<UPlantResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->PlantedAtUtcSeconds = PlantedAtUtcSeconds;
	Serializable->Message = Message;
	
	return Serializable;
}

void UPlantResultLibrary::Break(const UPlantResult* Serializable, bool& bSuccess, int64& PlantedAtUtcSeconds, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		PlantedAtUtcSeconds = Serializable->PlantedAtUtcSeconds;
		Message = Serializable->Message;
	}
		
}

