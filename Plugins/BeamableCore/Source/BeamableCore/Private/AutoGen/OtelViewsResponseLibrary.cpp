
#include "BeamableCore/Public/AutoGen/OtelViewsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOtelViewsResponseLibrary::OtelViewsResponseToJsonString(const UOtelViewsResponse* Serializable, const bool Pretty)
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

UOtelViewsResponse* UOtelViewsResponseLibrary::Make(TArray<UOtelView*> Views, UObject* Outer)
{
	auto Serializable = NewObject<UOtelViewsResponse>(Outer);
	Serializable->Views = Views;
	
	return Serializable;
}

void UOtelViewsResponseLibrary::Break(const UOtelViewsResponse* Serializable, TArray<UOtelView*>& Views)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Views = Serializable->Views;
	}
		
}

