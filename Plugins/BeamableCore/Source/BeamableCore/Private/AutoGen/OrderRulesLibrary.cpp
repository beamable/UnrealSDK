
#include "BeamableCore/Public/AutoGen/OrderRulesLibrary.h"

#include "CoreMinimal.h"


FString UOrderRulesLibrary::OrderRulesToJsonString(const UOrderRules* Serializable, const bool Pretty)
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

UOrderRules* UOrderRulesLibrary::Make(TArray<UOrderRule*> Orules, UObject* Outer)
{
	auto Serializable = NewObject<UOrderRules>(Outer);
	Serializable->Orules = Orules;
	
	return Serializable;
}

void UOrderRulesLibrary::Break(const UOrderRules* Serializable, TArray<UOrderRule*>& Orules)
{
	Orules = Serializable->Orules;
		
}

