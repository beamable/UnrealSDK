
#include "BeamableCore/Public/AutoGen/PASuggestedIndexLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPASuggestedIndexLibrary::PASuggestedIndexToJsonString(const UPASuggestedIndex* Serializable, const bool Pretty)
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

UPASuggestedIndex* UPASuggestedIndexLibrary::Make(FString Weight, FString Id, FString Namespace, TArray<FString> Impact, TArray<FString> Index, UObject* Outer)
{
	auto Serializable = NewObject<UPASuggestedIndex>(Outer);
	Serializable->Weight = Weight;
	Serializable->Id = Id;
	Serializable->Namespace = Namespace;
	Serializable->Impact = Impact;
	Serializable->Index = Index;
	
	return Serializable;
}

void UPASuggestedIndexLibrary::Break(const UPASuggestedIndex* Serializable, FString& Weight, FString& Id, FString& Namespace, TArray<FString>& Impact, TArray<FString>& Index)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Weight = Serializable->Weight;
		Id = Serializable->Id;
		Namespace = Serializable->Namespace;
		Impact = Serializable->Impact;
		Index = Serializable->Index;
	}
		
}

