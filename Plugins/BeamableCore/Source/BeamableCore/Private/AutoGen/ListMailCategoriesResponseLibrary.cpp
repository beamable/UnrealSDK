
#include "BeamableCore/Public/AutoGen/ListMailCategoriesResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListMailCategoriesResponseLibrary::ListMailCategoriesResponseToJsonString(const UListMailCategoriesResponse* Serializable, const bool Pretty)
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

UListMailCategoriesResponse* UListMailCategoriesResponseLibrary::Make(TArray<FString> Result, UObject* Outer)
{
	auto Serializable = NewObject<UListMailCategoriesResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UListMailCategoriesResponseLibrary::Break(const UListMailCategoriesResponse* Serializable, TArray<FString>& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

