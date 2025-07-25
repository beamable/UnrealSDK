
#include "BeamableCore/Public/AutoGen/VariableReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UVariableReferenceLibrary::VariableReferenceToJsonString(const UVariableReference* Serializable, const bool Pretty)
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

UVariableReference* UVariableReferenceLibrary::Make(FString Name, UObject* Outer)
{
	auto Serializable = NewObject<UVariableReference>(Outer);
	Serializable->Name = Name;
	
	return Serializable;
}

void UVariableReferenceLibrary::Break(const UVariableReference* Serializable, FString& Name)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
	}
		
}

