
#include "BeamableCore/Public/AutoGen/ContentTagFilterLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContentTagFilterLibrary::ContentTagFilterToJsonString(const UContentTagFilter* Serializable, const bool Pretty)
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

UContentTagFilter* UContentTagFilterLibrary::Make(TArray<FString> AllOf, TArray<FString> AnyOf, TArray<FString> NoneOf, UObject* Outer)
{
	auto Serializable = NewObject<UContentTagFilter>(Outer);
	Serializable->AllOf = AllOf;
	Serializable->AnyOf = AnyOf;
	Serializable->NoneOf = NoneOf;
	
	return Serializable;
}

void UContentTagFilterLibrary::Break(const UContentTagFilter* Serializable, TArray<FString>& AllOf, TArray<FString>& AnyOf, TArray<FString>& NoneOf)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AllOf = Serializable->AllOf;
		AnyOf = Serializable->AnyOf;
		NoneOf = Serializable->NoneOf;
	}
		
}

