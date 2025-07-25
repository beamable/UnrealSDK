
#include "BeamableCore/Public/AutoGen/ItemContentResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemContentResponseLibrary::ItemContentResponseToJsonString(const UItemContentResponse* Serializable, const bool Pretty)
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

UItemContentResponse* UItemContentResponseLibrary::Make(TArray<UItemArchetype*> Content, UObject* Outer)
{
	auto Serializable = NewObject<UItemContentResponse>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void UItemContentResponseLibrary::Break(const UItemContentResponse* Serializable, TArray<UItemArchetype*>& Content)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Content = Serializable->Content;
	}
		
}

