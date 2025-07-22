
#include "BeamableCore/Public/AutoGen/BeamoV2PASuggestedIndexLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2PASuggestedIndexLibrary::BeamoV2PASuggestedIndexToJsonString(const UBeamoV2PASuggestedIndex* Serializable, const bool Pretty)
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

UBeamoV2PASuggestedIndex* UBeamoV2PASuggestedIndexLibrary::Make(FString Id, FString Namespace, double Weight, TArray<FString> Impact, TArray<FMapOfInt32> Index, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2PASuggestedIndex>(Outer);
	Serializable->Id = Id;
	Serializable->Namespace = Namespace;
	Serializable->Weight = Weight;
	Serializable->Impact = Impact;
	Serializable->Index = Index;
	
	return Serializable;
}

void UBeamoV2PASuggestedIndexLibrary::Break(const UBeamoV2PASuggestedIndex* Serializable, FString& Id, FString& Namespace, double& Weight, TArray<FString>& Impact, TArray<FMapOfInt32>& Index)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Namespace = Serializable->Namespace;
		Weight = Serializable->Weight;
		Impact = Serializable->Impact;
		Index = Serializable->Index;
	}
		
}

