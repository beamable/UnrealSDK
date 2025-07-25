
#include "BeamableCore/Public/AutoGen/EventRuleLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventRuleLibrary::EventRuleToJsonString(const UEventRule* Serializable, const bool Pretty)
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

UEventRule* UEventRuleLibrary::Make(FString Rule, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UEventRule>(Outer);
	Serializable->Rule = Rule;
	Serializable->Value = Value;
	
	return Serializable;
}

void UEventRuleLibrary::Break(const UEventRule* Serializable, FString& Rule, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Rule = Serializable->Rule;
		Value = Serializable->Value;
	}
		
}

