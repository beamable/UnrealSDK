
#include "BeamableCore/Public/AutoGen/SearchExtendedRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USearchExtendedRequestBodyLibrary::SearchExtendedRequestBodyToJsonString(const USearchExtendedRequestBody* Serializable, const bool Pretty)
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

USearchExtendedRequestBody* USearchExtendedRequestBodyLibrary::Make(FString Domain, FString ObjectType, FString Access, TArray<UStatsSearchCriteria*> Criteria, TArray<FString> StatKeys, UObject* Outer)
{
	auto Serializable = NewObject<USearchExtendedRequestBody>(Outer);
	Serializable->Domain = Domain;
	Serializable->ObjectType = ObjectType;
	Serializable->Access = Access;
	Serializable->Criteria = Criteria;
	Serializable->StatKeys = StatKeys;
	
	return Serializable;
}

void USearchExtendedRequestBodyLibrary::Break(const USearchExtendedRequestBody* Serializable, FString& Domain, FString& ObjectType, FString& Access, TArray<UStatsSearchCriteria*>& Criteria, TArray<FString>& StatKeys)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Domain = Serializable->Domain;
		ObjectType = Serializable->ObjectType;
		Access = Serializable->Access;
		Criteria = Serializable->Criteria;
		StatKeys = Serializable->StatKeys;
	}
		
}

