
#include "BeamableCore/Public/AutoGen/OrderRuleLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOrderRuleLibrary::OrderRuleToJsonString(const UOrderRule* Serializable, const bool Pretty)
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

UOrderRule* UOrderRuleLibrary::Make(FString V, int32 O, UObject* Outer)
{
	auto Serializable = NewObject<UOrderRule>(Outer);
	Serializable->V = V;
	Serializable->O = O;
	
	return Serializable;
}

void UOrderRuleLibrary::Break(const UOrderRule* Serializable, FString& V, int32& O)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		V = Serializable->V;
		O = Serializable->O;
	}
		
}

