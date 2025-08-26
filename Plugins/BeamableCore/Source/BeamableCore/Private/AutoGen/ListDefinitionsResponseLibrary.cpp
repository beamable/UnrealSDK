
#include "BeamableCore/Public/AutoGen/ListDefinitionsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListDefinitionsResponseLibrary::ListDefinitionsResponseToJsonString(const UListDefinitionsResponse* Serializable, const bool Pretty)
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

UListDefinitionsResponse* UListDefinitionsResponseLibrary::Make(TArray<UAnnouncementDto*> Content, UObject* Outer)
{
	auto Serializable = NewObject<UListDefinitionsResponse>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void UListDefinitionsResponseLibrary::Break(const UListDefinitionsResponse* Serializable, TArray<UAnnouncementDto*>& Content)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Content = Serializable->Content;
	}
		
}

