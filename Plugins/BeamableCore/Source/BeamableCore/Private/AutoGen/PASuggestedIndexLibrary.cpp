
#include "BeamableCore/Public/AutoGen/PASuggestedIndexLibrary.h"

#include "CoreMinimal.h"


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

UPASuggestedIndex* UPASuggestedIndexLibrary::Make(FString Id, FString Namespace, double Weight, TArray<FString> Impact, TArray<FMapOfInt32> Index, UObject* Outer)
{
	auto Serializable = NewObject<UPASuggestedIndex>(Outer);
	Serializable->Id = Id;
	Serializable->Namespace = Namespace;
	Serializable->Weight = Weight;
	Serializable->Impact = Impact;
	Serializable->Index = Index;
	
	return Serializable;
}

void UPASuggestedIndexLibrary::Break(const UPASuggestedIndex* Serializable, FString& Id, FString& Namespace, double& Weight, TArray<FString>& Impact, TArray<FMapOfInt32>& Index)
{
	Id = Serializable->Id;
	Namespace = Serializable->Namespace;
	Weight = Serializable->Weight;
	Impact = Serializable->Impact;
	Index = Serializable->Index;
		
}

