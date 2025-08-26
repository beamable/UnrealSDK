
#include "BeamableCore/Public/AutoGen/ProblemDetailsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UProblemDetailsLibrary::ProblemDetailsToJsonString(const UProblemDetails* Serializable, const bool Pretty)
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

UProblemDetails* UProblemDetailsLibrary::Make(FOptionalString Type, FOptionalString Title, FOptionalInt32 Status, FOptionalString Detail, FOptionalString Instance, UObject* Outer)
{
	auto Serializable = NewObject<UProblemDetails>(Outer);
	Serializable->Type = Type;
	Serializable->Title = Title;
	Serializable->Status = Status;
	Serializable->Detail = Detail;
	Serializable->Instance = Instance;
	
	return Serializable;
}

void UProblemDetailsLibrary::Break(const UProblemDetails* Serializable, FOptionalString& Type, FOptionalString& Title, FOptionalInt32& Status, FOptionalString& Detail, FOptionalString& Instance)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Type = Serializable->Type;
		Title = Serializable->Title;
		Status = Serializable->Status;
		Detail = Serializable->Detail;
		Instance = Serializable->Instance;
	}
		
}

