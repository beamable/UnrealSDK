
#include "BeamableCore/Public/AutoGen/PASlowQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPASlowQueryLibrary::PASlowQueryToJsonString(const UPASlowQuery* Serializable, const bool Pretty)
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

UPASlowQuery* UPASlowQueryLibrary::Make(FString Line, FString Namespace, UObject* Outer)
{
	auto Serializable = NewObject<UPASlowQuery>(Outer);
	Serializable->Line = Line;
	Serializable->Namespace = Namespace;
	
	return Serializable;
}

void UPASlowQueryLibrary::Break(const UPASlowQuery* Serializable, FString& Line, FString& Namespace)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Line = Serializable->Line;
		Namespace = Serializable->Namespace;
	}
		
}

