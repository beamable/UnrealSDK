
#include "BeamableCore/Public/AutoGen/BeamoV2ProblemDetailsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ProblemDetailsLibrary::BeamoV2ProblemDetailsToJsonString(const UBeamoV2ProblemDetails* Serializable, const bool Pretty)
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

UBeamoV2ProblemDetails* UBeamoV2ProblemDetailsLibrary::Make(FOptionalString Type, FOptionalString Title, FOptionalInt32 Status, FOptionalString Detail, FOptionalString Instance, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ProblemDetails>(Outer);
	Serializable->Type = Type;
	Serializable->Title = Title;
	Serializable->Status = Status;
	Serializable->Detail = Detail;
	Serializable->Instance = Instance;
	
	return Serializable;
}

void UBeamoV2ProblemDetailsLibrary::Break(const UBeamoV2ProblemDetails* Serializable, FOptionalString& Type, FOptionalString& Title, FOptionalInt32& Status, FOptionalString& Detail, FOptionalString& Instance)
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

