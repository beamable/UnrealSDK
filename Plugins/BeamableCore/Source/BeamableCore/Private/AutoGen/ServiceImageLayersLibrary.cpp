
#include "BeamableCore/Public/AutoGen/ServiceImageLayersLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServiceImageLayersLibrary::ServiceImageLayersToJsonString(const UServiceImageLayers* Serializable, const bool Pretty)
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

UServiceImageLayers* UServiceImageLayersLibrary::Make(UBeamoBasicReference* Service, TArray<FString> Layers, UObject* Outer)
{
	auto Serializable = NewObject<UServiceImageLayers>(Outer);
	Serializable->Service = Service;
	Serializable->Layers = Layers;
	
	return Serializable;
}

void UServiceImageLayersLibrary::Break(const UServiceImageLayers* Serializable, UBeamoBasicReference*& Service, TArray<FString>& Layers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		Layers = Serializable->Layers;
	}
		
}

