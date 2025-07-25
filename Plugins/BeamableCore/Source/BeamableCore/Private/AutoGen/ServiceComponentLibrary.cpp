
#include "BeamableCore/Public/AutoGen/ServiceComponentLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServiceComponentLibrary::ServiceComponentToJsonString(const UServiceComponent* Serializable, const bool Pretty)
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

UServiceComponent* UServiceComponentLibrary::Make(FString Name, UObject* Outer)
{
	auto Serializable = NewObject<UServiceComponent>(Outer);
	Serializable->Name = Name;
	
	return Serializable;
}

void UServiceComponentLibrary::Break(const UServiceComponent* Serializable, FString& Name)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
	}
		
}

