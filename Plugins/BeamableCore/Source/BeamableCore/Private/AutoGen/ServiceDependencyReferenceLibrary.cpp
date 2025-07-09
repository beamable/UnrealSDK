
#include "BeamableCore/Public/AutoGen/ServiceDependencyReferenceLibrary.h"

#include "CoreMinimal.h"


FString UServiceDependencyReferenceLibrary::ServiceDependencyReferenceToJsonString(const UServiceDependencyReference* Serializable, const bool Pretty)
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

UServiceDependencyReference* UServiceDependencyReferenceLibrary::Make(FOptionalString Id, FOptionalString StorageType, UObject* Outer)
{
	auto Serializable = NewObject<UServiceDependencyReference>(Outer);
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	
	return Serializable;
}

void UServiceDependencyReferenceLibrary::Break(const UServiceDependencyReference* Serializable, FOptionalString& Id, FOptionalString& StorageType)
{
	Id = Serializable->Id;
	StorageType = Serializable->StorageType;
		
}

